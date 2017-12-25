#include "ofApp.h"

void ofApp::setup() {
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    
    // this sets the camera's distance from the object
    cam.setDistance(1000);
    cam.disableMouseInput();
    cam.disableRotation();
    cam.setFarClip(-100);
    
    //
    // set when <control> key is held down
    //
    selectedImage = NULL;
}

void ofApp::update() {
    
}

void ofApp::draw() {
    cam.begin();
    ofBackground(0);
    ofFill();
    
    for (int i = 0; i < images.size(); i++ ) {
        images[i]->draw();
    }
    
    cam.end();
}

//
// delete all images in list on exit
//
void ofApp::exit() {
    for (int i = 0; i < images.size(); i++) {
        delete images[i];
    }
}

void ofApp::keyPressed(int key) {
    switch (key) {
        case 'C' | 'c':
            if (cam.getMouseInputEnabled()) cam.disableMouseInput();
            else cam.enableMouseInput();
            break;
            // Select a single image and delete it from the Canvas
        case 'D' | 'd':
            deleteImage();
            break;
        case 'F' | 'f':
            ofToggleFullscreen();
            break;
            // Rotate image
        case 'R' | 'r':
            rotateImage();
            break;
            // Save file
        case 'S' | 's':
            ofSaveFrame();
            break;
            // Scale down
        case 'T' | 't':
            scaleDown();
            break;
            // Scale up
        case 'U' | 'u':
            scaleUp();
            break;
            // Move right
        case OF_KEY_RIGHT:
            moveImageRight();
            break;
            // Move left
        case OF_KEY_LEFT:
            moveImageLeft();
            break;
            // Move up
        case OF_KEY_UP:
            moveImageUp();
            break;
            // Move down
        case OF_KEY_DOWN:
            moveImageDown();
            break;
        case OF_KEY_ALT:
            cam.enableMouseInput();
            break;
            
    }
}

void ofApp::keyReleased(int key) {
    switch (key) {
        case OF_KEY_DOWN | OF_KEY_UP | OF_KEY_RIGHT | OF_KEY_LEFT:
            draw(); // redraw
            break;
        case OF_KEY_ALT:
            cam.disableMouseInput();
            break;
    }
}

void ofApp::mouseMoved(int x, int y ) {
    
}

void ofApp::mouseDragged(int x, int y, int button) {
}

void ofApp::mousePressed(int x, int y, int button) {
    renderSelection();
    processSelection(x, y);
}

void ofApp::mouseReleased(int x, int y, int button) {
    draw(); // redraw
}

void ofApp::mouseEntered(int x, int y) {
    
}

void ofApp::mouseExited(int x, int y) {
    
}

void ofApp::windowResized(int w, int h) {
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
    
}

//--------------------------------------------------------------
//
// Simple file drag and drop implementation.
//
void ofApp::dragEvent(ofDragInfo dragInfo) {
    
    Image *imageObj = new Image();
    imageObj->trans = cam.screenToWorld(dragInfo.position);
    if (imageObj->image.load(dragInfo.files[0]) == true)
        images.push_back(imageObj);
    else {
        cout << "Can't load image: " << dragInfo.files[0] << endl;
        delete imageObj;
    }
}

void ofApp::rotateImage()
{
    if (selectedImage) selectedImage->image.rotate90(45);
}

void ofApp::deleteImage()
{
    selectedImage->image.clear();
}

void ofApp::moveImageRight()
{
    if (selectedImage) selectedImage->trans.x = selectedImage->trans.x + 10;
}

void ofApp::moveImageLeft()
{
    if (selectedImage) selectedImage->trans.x = selectedImage->trans.x - 10;
}

void ofApp::moveImageUp()
{
    if (selectedImage) selectedImage->trans.y = selectedImage->trans.y + 10;
}

void ofApp::moveImageDown()
{
    if (selectedImage) selectedImage->trans.y = selectedImage->trans.y - 10;
}

void ofApp::scaleUp()
{
    if (selectedImage)
    {
        selectedImage->scale.x = selectedImage->scale.x + 0.1;
        selectedImage->scale.y = selectedImage->scale.y + 0.1;
    }
}

void ofApp::scaleDown()
{
    if (selectedImage)
    {
        selectedImage->scale.x = selectedImage->scale.x - 0.1;
        selectedImage->scale.y = selectedImage->scale.y - 0.1;
    }
    
}

//
// Render for the purposes of selection hit testing.  In this case
// we use the color method. We render echo object as a different
// value of r,g,b.  We then compare the pixel under the mouse. The
// value is the index into the image list;
//
void ofApp::renderSelection() {
    cam.begin();
    ofBackground(0);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    for (int i = 0; i < images.size(); i++) {
        images[i]->draw(true, i);
    }
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    cam.end();
}

void ofApp::processSelection(int x, int y) {
    unsigned char res[4];
    GLint viewport[4];
    
    // read pixel under mouse x y
    //
    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
    
    if (selectedImage) {
        selectedImage->bSelected = false;
        selectedImage = NULL;
    }
    
    //
    //  lookup image by color of pixel
    //
    if (res[0] > 0 && res[0] <= images.size()) {
        Image *image = images[res[0] - 1];
        image->bSelected = true;
        selectedImage = image;
        
        // move selected image to beginning of list
        //
        images.erase(images.begin() + (res[0] - 1) );
        images.push_back(image);
    }
    
}

Image::Image()
{
    trans.x = 0;
    trans.y = 0;
    scale.x = 1.0;
    scale.y = 1.0;
    rot = 0;
    bSelected = false;
}

void Image::draw(bool bSelectMode, int index) {
    ofPushMatrix();
    ofTranslate(trans);
    ofScale(scale);
    ofRotate(rot);
    
    //
    // if drawing image normally
    //
    if (!bSelectMode) {
        
        //
        // if selected, draw a light yellow box around image
        //
        if (bSelected) {
            ofNoFill();
            ofSetColor(255, 255, 0);
            ofSetLineWidth(20);
            ofDrawRectangle(-image.getWidth() / 2.0, -image.getHeight() / 2.0,
                            image.getWidth(), image.getHeight());
        }
        ofSetColor(255, 255, 255, 255);
        image.draw(-image.getWidth() / 2.0, -image.getHeight() / 2.0);
        
    }
    //
    // else if drawing to test selection
    //
    else {
        ofFill();
        ofSetColor(index + 1, 0, 0);
        ofDrawRectangle(-image.getWidth() / 2.0, -image.getHeight() / 2.0,
                        image.getWidth(), image.getHeight());
    }
    ofPopMatrix();
}