
#include "animation.h"
#include "gif-h/gif.h"

Animation::Animation(AnimationEventEmitter &emitter) :
    activeFrameIndex(-1),  dim(Animation::DEFAULT_DIMENSION), emitter(emitter) {
    std::unique_ptr<Frame> frame(new Frame(emitter, dim));
    frames.insert(frames.end(), std::move(frame));
    activeFrameIndex = 0;
}

void Animation::addFrame(int index) {
    if (index < 0 || index > (int)frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    std::unique_ptr<Frame> f(new Frame(emitter, dim));
    addFrameInternal(std::move(f), index);
    emitter.emitAddFrameEvent(new AddFrameAction(this, index));
}

void Animation::addFrameInternal(std::unique_ptr<Frame> f, int index) {
    frames.insert(frames.begin() + index, std::move(f));
    if (activeFrameIndex >= index){
        activeFrameIndex++;
    }
}

void Animation::moveFrame(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= (int)frames.size() ||
        toIndex < 0 || toIndex >= (int)frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    moveFrameInternal(fromIndex, toIndex);
    emitter.emitMoveFrameEvent(new MoveFrameAction(this, fromIndex, toIndex));
}

void Animation::moveFrameInternal(int fromIndex, int toIndex) {
    auto frame = std::move(frames[fromIndex]);
    frames.erase(frames.begin() + fromIndex);
    frames.insert(frames.begin() + toIndex, std::move(frame));
    if (activeFrameIndex == fromIndex) {
        activeFrameIndex = toIndex;
    } else if (fromIndex < toIndex &&
               activeFrameIndex > fromIndex &&
               activeFrameIndex <= toIndex){
        activeFrameIndex--;
    } else if (fromIndex > toIndex &&
               activeFrameIndex >= toIndex &&
               activeFrameIndex < fromIndex) {
        activeFrameIndex++;
    }
}

void Animation::removeFrame(int index) {
    if (frames.size() <= 1) {
        throw std::invalid_argument("An animation must have at least one frame.");
    }
    if (index < 0 || index >= (int)frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    auto frame = std::move(frames[index]);
    removeFrameInternal(index);
    emitter.emitRemoveFrameEvent(new RemoveFrameAction(this, std::move(frame), index));
}

void Animation::removeFrameInternal(int index) {
    if (index < activeFrameIndex || (index == activeFrameIndex &&
                                     activeFrameIndex == (int)frames.size() - 1)) {
        activeFrameIndex--;
    }
    frames.erase(frames.begin() + index);
}

void Animation::setActiveFrame(int index) {
    if (index < 0 || index >= (int)frames.size()) {
        throw std::invalid_argument("Index out of bounds.");
    }
    activeFrameIndex = index;
}

int Animation::activeFrameIdx() const {
    return activeFrameIndex;
}

Frame &Animation::activeFrame() {
    return *frames.at(activeFrameIndex);
}

void Animation::resize(int dimension) {
    if (dimension < 8) {
        throw std::invalid_argument("Resize dimension must be at least 8.");
    }
    int before = dim;
    resizeInternal(dimension);
    emitter.emiteResizeEvent(new ResizeAction(this, before, dimension));
}

int Animation::dimension() const {
    return dim;
}

void Animation::resizeInternal(int dimension) {
    this->dim = dimension;
    for (auto& frame : frames) {
        frame->resize(dim);
    }
}

int Animation::numframes() const {
    return frames.size();
}

std::vector<std::unique_ptr<Frame>>& Animation::getFrames(){
    return frames;
}

void saveImage(std::ostream& out, QImage& image) {
    for (int row = 0; row < image.height(); row++) {
        for (int col = 0; col < image.width(); col++) {
            QColor color = image.pixelColor(row, col);
            out << color.red() << " " <<
                color.green() << " " <<
                color.blue() << " " <<
                color.alpha();
            if (col != image.width() - 1) {
                out << " ";
            }
        }
        out << std::endl;
    }
}

void Animation::save(std::ostream& out) const {
    out << dim << " " << dim << std::endl; // height and width
    out << numframes() << std::endl;
    for (auto& frame : frames) {
        QImage image = frame->image();
        saveImage(out, image);
    }
}

void Animation::saveExtendedFormat(std::ostream& out) const {
    out << "P O L I T O" << std::endl; // Write the *magic* header.
    out << dim << " " << dim << std::endl;
    out << numframes() << std::endl;
    for (auto& frame : frames) {
        out << frame->duration() << std::endl;
        out << frame->numlayers() << std::endl;
        for (auto& layer : frame->getLayers()) {
            QImage image = layer->pixmap().toImage();
            saveImage(out, image);
        }
    }
}

// Returns whether the stream begins with the extended
// format header.
bool checkForExtendedHeader(std::istream& in) {
    auto startPos = in.tellg();
    std::string line;
    if (std::getline(in, line)) {
        if (line == "P O L I T O") return true;
        in.seekg(startPos);
    }
    return false;
}

void loadImage(std::istream& in, QImage& image) {
    for (int row = 0; row < image.height(); row++) {
        for (int col = 0; col < image.width(); col++) {
            int red, green, blue, alpha;
            in >> red >> green >> blue >> alpha;
            if (in.fail()) {
                throw std::runtime_error(
                                         "Unable to load: file contained misformatted or mis-sized frame section.");
            }
            QColor color(red, green, blue, alpha);
            image.setPixelColor(row, col, color);
        }
    }
}

Frame *loadExtendedFrame(std::istream& in, AnimationEventEmitter& emitter, int dimension) {
    int duration, numLayers;
    in >> duration >> numLayers;
    if (in.fail() || numLayers < 1) {
        throw std::runtime_error(
                                 "Unable to load: file contained misformatted extended-frame header.");
    }
    std::vector<std::unique_ptr<Layer>> layers;
    for (int i = 0; i < numLayers; i++) {
        QImage image(dimension, dimension, QImage::Format_RGBA8888);
        loadImage(in, image);
        layers.push_back(std::unique_ptr<Layer>(new Layer(image)));
    }
    // Pass ownership of the layers to the new frame.
    Frame *frame = new Frame(emitter, layers);
    if (duration > 0) frame->setDuration(duration);
    return frame;
}

Frame *loadFrame(std::istream& in, AnimationEventEmitter& emitter, int dimension) {
    QImage image(dimension, dimension, QImage::Format_RGBA8888);
    image.fill(Qt::transparent);
    loadImage(in, image);
    return new Frame(emitter, image);
}

void Animation::load(std::istream& in) {
    bool extendedFormat = checkForExtendedHeader(in);
    int width, height, numFrames;
    in >> width >> height >> numFrames;
    if (in.fail() || width != height || numFrames == 0) {
        throw std::runtime_error(
                                 "Unable to load: file contained misformatted width, height, nframes header.");
    }
    std::vector<std::unique_ptr<Frame>> tempFrames;
    for (int i = 0; i < numFrames; i++) {
        Frame *frame = extendedFormat ?
            loadExtendedFrame(in, emitter, height) : loadFrame(in, emitter, height);
        tempFrames.push_back(std::unique_ptr<Frame>(frame));
    }
    dim = height;
    activeFrameIndex = 0;
    frames.clear();
    for (int i = 0; i < (int)tempFrames.size(); i++) {
        frames.push_back(std::move(tempFrames.at(i)));
    }
}

void Animation::saveGif(std::string filename) const {
   QColor newColor = QColorDialog::getColor(QColor(255,0,255), nullptr, "Select GIF Background Color" );
   if( !newColor.isValid() ) {
       newColor = QColor(255,0,255);
   }
   GifWriter writer;
   GifBegin( &writer, filename.c_str(), dimension(), dimension(), 100, 8, true );
   for (int i=0;i<frames.size();i++) {
       Frame* frame = frames[i].get();
       QImage image = frame->image();
       QImage newImage(image.width(), image.height(), QImage::Format_RGBA8888);
       newImage.fill(newColor);
       QPainter painter(&newImage);
       painter.drawImage(0,0,image);
       GifWriteFrame( &writer, newImage.bits(), dimension(), dimension(), frame->duration()/10, 8, true);
   }
   GifEnd( &writer );
}
