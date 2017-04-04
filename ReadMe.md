# Hello 2D: A 2D graphics primer

A presentation on 2D rendering concepts and a sample app. to go with it.  The concepts explained are API-agnostic; Direct2D is used here for demonstration.

[`presentation.md`](https://github.com/legends2k/Hello2D/blob/master/presentation.md) has the presentation content in Markdown foramt.  You need Pandoc to generate the presentation

    pandoc -t beamer -V theme:Malmoe -V colortheme:wolverine -V colorlinks:true presentation.md -o 2d_graphics.pdf

Feel free to send a pull request to improve the code or the presentation.
