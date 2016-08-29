#include <iostream>
#include <string>
#include <fstream>
#include "SArgReader.h"

using namespace std;

bool getPlot(SArgReader &args, string &plot);
string addHeader(string title);
string addFooter();
void handleFlag(SArgReader & args);

int main(int argc, char *argv[]) {
  SArgReader args(argc, argv);

  string plot = "";
  string fileName = "/home/stephen/web/plots/";

  // Get the actual plot
  if ( !getPlot(args, plot) ) {
    cerr << "To use fooplot you need to supply a function as a command line argument." << endl;
    return 1;
  }
  string tempName = "";
  string fullFile = addHeader(plot);
  bool firstTime = true;
  do {
    cout << "plot is " << plot << endl;
    fullFile += " myPlot.addPlot('";
    fullFile += plot;
    fullFile += "',FOOPLOT_TYPE_FUNCTION);\n";
    if ( !firstTime )
      tempName += "_";
    firstTime = false;
    tempName += plot;
  } while ( getPlot(args,plot) );
  fullFile += addFooter();

  ofstream out;
  string plotStripped = "";
  for ( int i = 0; i < tempName.length(); i++ ) {
    if ( tempName[i] != '/')
      plotStripped += tempName[i];
    else
      plotStripped += '\\';
  }
  fileName += plotStripped + ".html";
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

bool getPlot(SArgReader &args, string &plot) {
  plot = "";
  if ( args.flagExists() ) {
    handleFlag(args);
  }
  else if ( args.empty() ) {
    return false;
  }
  else {
    args.nextString(plot);
  }
}

void handleFlag(SArgReader & args) {
  // do nothing right now
  args.remove(); // erase the current flag.
}
