fooplot
=======
Command line tool based on fooplot.com. This is a fork of [github.com/dheera/fooplot]dheera/fooplot . A Javascript-based plot program that generates an html file for viewing multiple functions.

### Dependencies:
- Premake5
- G++
- HTML/Javascript

### Building:
- Use premake5 to create makefiles or appropriate project files for your system.
- Build the project using make, or appropriate tool.

#### Linux example:
premake5 gmake
sudo make

### Running:
fooplot function
where function looks along the lines of "x^2" "x+5*sin(x)"
You will need to make sure you install the web_install/fooplot.js file to where you want the generated html files to go.

### ToDo:
- Create command line flags for fine-tuning of the plots. Things like manual coloring, etc.
- Create automated coloring of the functions.
- Better platform compatibility, currently only supporting linux.
- Perhaps a premake5 flag that places the fooplot.js in a designated directory.
- Command-line flag for specifying output file name, and one for specifying target directory.
