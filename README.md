

# Face detection and Face recognizer using opencv

## Usage: 
    mkdir build cd build cmake ../ make

### Simple face recoginition and send email when unknown face is detected.
    create your csv like below
        /path/13.jpg;13 /path/11.jpg;11 /path/12.png;12
    read csv files and load images
    create the facerecognizer and train
    if the confidence is less then 80 then user gets an email of the person

# Dependenies:
1.opencv and opencv_contrib
2.libquickmail tried with curl to send email however attchment in mail was not possible for me.
