#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "SArgReader.h"

using namespace std;

vector<string> colorCode;
vector<string> colorName;

void setUpColors();
bool checkColor(string & c);
bool getPlot(SArgReader &args, string &plot);
string addHeader(string title);
string addFooter();
void handleFlag(SArgReader & args);
string cleanFileName(string filename);

int main(int argc, char *argv[]) {
  setUpColors();
  SArgReader args(argc, argv);
  vector<string> plots;
  vector<string> colors; string tempColor;

  string plot = "";
  string fileName = "/home/stephen/web/plots/";
  string outputFileName = "";
  // Loop through all arguments:
  while ( !args.empty() ) {
    // For each argument, check if it is a flag.
    if ( args.checkFlag("-o") ) {
      if ( !args.nextString(outputFileName) ) {
        cerr << "Error: If you specify the -o flag you must follow it with the name of the output file." << endl;
        return -1;
      }
    }
    else if ( args.checkFlag("-c") || args.checkFlag("-color")) {
      if ( !args.nextString(tempColor)) {
        cerr << "Error: If you specify the -c or -color flag you must follow it with the name of the output file." << endl;
        return -2;
      }
      // add this to the colors list
      // have a check that makes sure the color is an appropriate color
      // have global strings at the top that map to the appropriate colors
      // something like "RED" = red color
      // also allow for them to put colors in the js format
      if ( !checkColor(tempColor) ) {
        cerr << "Error: When specifying a color, you muse use a color that is in the format of #000000, or use one of the preset colors as follows: " << endl;
        return -3;
      }
      colors.push_back(tempColor);
    }
    else {
      // finally check if it is a string/plot:
      string tempPlotIn = "";
      args.nextString(tempPlotIn);
      // make sure this is an actual plot:

      plots.push_back(tempPlotIn);
    }
  }

  // Get the actual plot
  if ( plots.size() < 1 ) {
    cerr << "To use fooplot you need to supply a function as a command line argument." << endl;
    return 1;
  }

  string tempName = outputFileName;
  string fullFile = addHeader(plot);

  for ( int i = 0; i < plots.size(); i++ ) {
    cout << "plot is " << plots[i] << endl;
    fullFile += " myPlot.addPlot('";
    fullFile += plots[i];
    fullFile += "',FOOPLOT_TYPE_FUNCTION";
    if ( colors.size() > i ) {
      fullFile += ",{'color':'";
      fullFile += colors[i];
      fullFile += "'}";
    }
    fullFile += ");\n";
    if ( outputFileName.length() < 1 ) {
      tempName += plots[i];
      if ( i + 1 < plots.size() ) {
        tempName += "_";
      }
    }
  }
  fullFile += addFooter();

  ofstream out;

  fileName += cleanFileName(tempName) + ".html";
  out.open(fileName.c_str());
  if ( !out ) {
    cerr << "There was an error opening the output file. Please ensure that the destination exists. The file name in question was: " << fileName << endl;
    return 2;
  }
  out << fullFile << endl;
  out.close();
  cout << "File created at: " << fileName << endl;
  return 0;
}

string addHeader(string title) {
  string returnValue = "<!doctype html>\n<html>\n<head>\n<title>";
  returnValue += title;
  returnValue += "</title>\n<script type='text/javascript' src='fooplot.js'>";
  returnValue += "</script>\n<script type='text/javascript'>\n\nfunction main() {\n";
  returnValue += " myPlot = new Fooplot(document.getElementById('myPlot'));\n";
  return returnValue;
}

string addFooter() {
  string returnValue = " myPlot.reDraw();\n}\n\n</script>\n</head>\n\n<body onload='main();'>\n\n";
  returnValue += "<div id='myPlot' style='width:1080px;height:720px;'></div>\n\n";
  returnValue += "</body>\n</html>";
  return returnValue;
}

string cleanFileName(string filename) {
  string filenameStripped = "";
  for ( int i = 0; i < filename.length(); i++ ) {
    if ( filename[i] != '/')
      filenameStripped += filename[i];
    else
      filenameStripped += '\\';
  }
  return filenameStripped;
}

void setUpColors() {
  colorName.push_back("RED");
  colorCode.push_back("#FF0000");
}

bool checkColor(string & c) {
  for ( int i = 0; i < colorName.size(); i++ ) {
    if ( c == colorName[i] ) {
      c = colorCode[i];
      return true;
    }
  }
  if ( c[0] == '#' && c.length() == 7 ) {
    return true;
  }
  return false;

}
