# 2D Graphics Primer

A presentation on 2D rendering concepts and a sample app. to go with it.  The concepts explained are API-agnostic; [Direct2D](https://msdn.microsoft.com/en-us/library/windows/desktop/dd372337(v=vs.85).aspx) is used here for demonstration.

## Slide Deck

It's a PDF presentation.  To only view it, see [`2d_graphics.pdf`](https://github.com/legends2k/Hello2D/blob/master/2d_graphics.pdf).

If you intend to edit the slides, [`presentation.md`](https://github.com/legends2k/Hello2D/blob/master/presentation.md) has the content in [Markdown](http://daringfireball.net/projects/markdown/basics).  It's just a plain text file, use your favouritve text editor.  To compile it into a PDF you would need

* XeLaTeX
* PdfTeX
* [Pandoc](http://pandoc.org/)

to generate the presentation thus

    pandoc --latex-engine=xelatex -t beamer -V theme:Malmoe -V colortheme:wolverine -V colorlinks:true -V mainfont:'Segoe UI' -o 2d_graphics.pdf presentation.md

## Code

The source code goes into the `/src` folder. The project is tested to work on Windows 10 with Visual Studio 2015 and 2017.

If you are using Visual Studio 2017, it does not automatically retarget the project configuration at times and the compiler may crib at you during first build.  In that case, go to *Project Properties* → *Configuration Properties* → *General* and change the `Platform Toolset` to `Visual Studio 2017 (v141)`.  It should compile without any issues now.

Feel free to send a pull request to improve the code or the presentation.
