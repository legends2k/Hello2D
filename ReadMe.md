# 2D Graphics Primer

A presentation on 2D rendering concepts and a sample app. to go with it.  The concepts explained are API-agnostic; [Direct2D](https://msdn.microsoft.com/en-us/library/windows/desktop/dd372337(v=vs.85).aspx) is used here for demonstration.  The project is tested to work on Windows 10 with Visual Studio 2015 and 2017.

[`presentation.md`](https://github.com/legends2k/Hello2D/blob/master/presentation.md) has the content in Markdown format.  You would need

* XeLaTeX
* PdfTeX
* [Pandoc](http://pandoc.org/)

to generate the presentation thus

    pandoc --latex-engine=xelatex -t beamer -V theme:Malmoe -V colortheme:wolverine -V colorlinks:true -V mainfont:'Segoe UI' -o 2d_graphics.pdf presentation.md

Feel free to send a pull request to improve the code or the presentation.