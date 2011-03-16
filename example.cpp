#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "ResourceFile.h"

int main()
{
    {
        // write test
        cout << "Write Test:" << endl;

        ResourceFileWriter writeTest("writeTest.dat");
        writeTest.addEntry("ball.png", "files/ball.png");
        writeTest.addEntry("audio.mp3", "files/audio.mp3");
        writeTest.addEntry("Text Document.txt", "files/Text Document.txt");
        writeTest.addEntry("icon.png", "files/icon.png");
        writeTest.write();

        vector<string> entryNamesList = writeTest.getEntryNames();

        cout << "The following files were added to writeTest.dat." << endl;
        for(vector<string>::iterator i = entryNamesList.begin(); i != entryNamesList.end(); i++)
        {
            string entryName = (*i);
            cout << entryName << endl;
        }
    }

    cout << endl << endl;

    {
        // read test
        cout << "Read Test:" << endl;

        ResourceFileReader readTest("writeTest.dat");
        readTest.read();

        vector<string> entryNamesList = readTest.getEntryNames();

        cout << "The following files are in writeTest.dat." << endl;
        for(vector<string>::iterator i = entryNamesList.begin(); i != entryNamesList.end(); i++)
        {
            string entryName = (*i);
            cout << entryName << " (" << readTest.getEntryFileSize(entryName) << " bytes)" << endl;
        }
    }

    return 0;
}
