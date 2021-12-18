#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //place your media files in the bin/data
    myVidPlayer.load("Lim3.mp4");
    myVidPlayer.play();
    myVidPlayer.setLoopState(OF_LOOP_NORMAL);
    sound.load("S5.wav");
    sound.play();
    sound.setLoop(true);
    ofSetBackgroundColor(0);
    bHide = false;
    
    Gui.setup();
    Gui.add(volume.set("volume",0.5, 0, 1.0));
    Gui.add(visDecay.set("visDecay", 0.5, 0, 1.0));
    //You can change these for different results- just change the range of the GUI
    Gui.add(myWidth.set("width",120., 40., 1200.));
    Gui.add(myHeight.set("height", 480., 40., 600.));
    Gui.add(myMultiplier.set("multiply", 100000, 9500000, 500000));
    
    fft=new float [128];//can be changed we can not have more bands than fft  Also, it needs to be things like 32, 64, 128, 254...I am not going to go into the maths but yes, it is true and there is lots of info online about fft processes and why :)
    for (int i =0; i <128; i++){
        fft[i]=0;
    }
    //bands should be half the fft float.
    bands=64;
}

//--------------------------------------------------------------
void ofApp::update(){
    myVidPlayer.update();
    ofSoundUpdate();//needed with bigger projects to avoid dropouts/crashes.
    sound.setVolume(volume);
    soundSpectrum = ofSoundGetSpectrum(bands);
    for (int i =0; i<bands; i++){
        fft[i] *= visDecay;
        if (fft[i]<soundSpectrum[i]){
            fft[i]=soundSpectrum[i];
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //note to self- it needs to be += for the syntax to work
    for (int k =0; k < bands; k++){
        for (int i = 0; i < ofGetWidth(); i += myWidth){
            for (int j = 0; j < ofGetHeight(); j += myHeight){
                float a = i * myMultiplier;
                float newWidth = myWidth * ((fft[k]) + a);
                float newHeight = myHeight + ((fft[k]) * i);
                    myVidPlayer.draw(i,j,newWidth,newHeight);
                //Remember, you can always print stuff to the console but it can be expensive
                //cout<<newWidth<<endl;
       
       }
   }
    }
    if( !bHide ){
        Gui.draw();
}
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //show or hide the GUI by pressing "h"
    if( key == 'h' ){
        bHide = !bHide;
    }
}


