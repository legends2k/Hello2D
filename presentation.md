% 2D Graphics Primer
% Sundaram Ramaswamy
% April, 2017

# Good 'ol drawing

1. Let's draw something simple!
2. Map backwards by learning the theory :)
3. See code to seal the understanding
4. _Rise, repeat_

> **Disclaimer**: This is a primer.  Chances are you might know a lot more than the presenter and the presented!

# Reasons

* Prefer breadth-wise coverage
    + Allows to cover more concepts
    + Pretty pictures are better motivators :)
    + Learning concepts in isolation doesn't encourage you to jump-in
    + Beginners wouldn't appricate digging deep; can always do it alone once motivated
* Favour intuition over rigour
    + Tries to be an "enabler" not a _Reference Guide_
* Concepts are API-agnostic
    + D2D used here but works just as well in say HTML5 canvas, SDL, etc.

# Let's Draw!

![Paths, strokes and fills](./img/output1.png "Scenery"){ width=100% height=100% }


# Concept: Path / Geometry

* A *mathy* way to remember an artist's work
    + Store every point
        * Where did he put his brush down?
    + Store every hand move
        * Did he draw a line or a curve?

> Example: move to `(5, 5)`, line to `(10, 5)`

* It's just data about **shapes**
    + Hear path/geometry, think **shapes**
    + Data by itself
        * Doesn't talk about how it's used
        * Doesn't depend on hardware/device
        * is plain-old data; no magic
* Once stored this way, any _reader_ can imitate the artist
    + Reader may be a human, computer, graph plotter, …

# Path (contd.)

* Commands: `move to`, `line to`, `curve to`, `arc to`, …
    + Curves are quadratic and cubic Bézier curves
* Each figure has `begin` and `end` (with/out `close`)
    + `close` closes by drawing a line between first and last points
* Don't be intimidated by path drawing languages
    + Just shorthand notations for these commands
    + It’s cumbersome to construct figures otherwise
    + [XAML](https://msdn.microsoft.com/en-us/library/ms752293.aspx): `M 10, 100 L 20, 100`
    + PDF: `10 100 m 20 100 l`
* Represent any artibrary shape: polygon
* Multiple disjoint figures within a single path geometry

# Drawing paths: stroke

One, obvious, way to use paths: draw them

**Stroke**: trace the outline of the geometry's figures.

The brush used by the artist has

+ Colour
+ Thickness
+ Dash pattern: think _dotted line_
+ Line cap style
    * Butt cap  `|---|`
    * Round cap `(---)`
    * Square cap `| --- |`
+ Line join style
    * Round join `u`
    * Round join `\_/`
    * Miter join `V`
+ Miter limit: max height when joining two line ends

# Drawing paths: fill

* Filling the interior of a path with some brush
    + When unclosed, it's implicitly closed by D2D
    + PDF doesn't honour fill, if unclosed
* But wait, what's *inside* for
    + One sub-path inside another?
    + Self-intersecting paths?
* [Winding rule](https://msdn.microsoft.com/en-us/library/windows/desktop/dd368110(v=vs.85).aspx)
    + Even-odd
    + Non-zero

# Even = fill, Odd = no fill
![Even Odd rule](./img/even_odd.png "Even Odd"){ width=100% height=100% }

> Credit: MSDN

# Non-zero Fill
![Non-zero rule](./img/nonzero.png "Non-zero"){ width=50% height=50% }

> Credit: MSDN

# Resource: Brushes

Brushes, also called, **pens** do stroking & filling

Didn’t speak about its colour thus far; it can be

+ Constant
    * Solid: refers the same colour always
+ Varies by position
    + Gradient: get colour based on a function of position
        + Linear
        + Radial
    + Bitmap
        * Get colour from a lookup table

# Concept: Colours

* Need a precise way of representing colours
* Colour spaces
    + RGB
    + HSV and HSL
    + CMYK
    + many more
* Most rendering APIs work in RGB
    + Additive colour system
    + This is how display systems work
    + Easy math: simple calculations
* HSV is preferred by artists
    + Most aesthetically pleasing
    + Better for colour pickers

# Pixel formats

* Colour value is math; its realisation in hardware leads to

> **Pixel**: picture element

* Irrespective of colour space, data type decides richness
    + Wider the format, richer the gamut
* Integer formats: `0` darkest; `max(channel width)` brightest
    + 32-bit pixel formats: `A8 R8 G8 B8`, `R8 G8 B8 A8`, …
    + 24-bit pixel formats: `R8 G8 B8`, …
    + 16-bit pixel formats: `R5 G6 B5`, `A4 R4 G4 B4`, `R5 G5 B5`, …
    + 8-bit pixel formats: indexing a predefined colour palette
* Floating-point formats: `0.0` darkest, `1.0` brightest
    + Costly: `4 * 32 = 128` bits for RGBA
    + Better for image manipulation
* If exceeds during calculation, it's `clamp` ed by `min` and `max`

# Concept: Interpolation

**Idea**: Given two values, guess/find values in between

> 0 ● ——————×—————— ○ 1

* Colour at `0` is black `(0, 0, 0)`
* Colour at `1` is white `(1, 1, 1)`
* What's the colour at `½`?
* It's pure grey: `(½, ½, ½)`.  But how?
* Works with any values: position (any dimension), temperature, say even chilli hotness – scoville heat index, etc.

# Linear Interpolation a.k.a lerp

$$
\boxed{L(t) = P_0 + t (P_1 - P_0)}
$$

\begin{align*}
P_0 = (0, 0, 0) && P_1 = (1, 1, 1) \\
L(0) = (0, 0, 0) && L(1) = (1, 1, 1) && L(\frac{1}{2}) = (\frac{1}{2}, \frac{1}{2}, \frac{1}{2})
\end{align*}


# Radial Interpolation

# Bitmap Brushes

# Tiling and Pattern Brushes

# Transformations

* Concise representation of changes to points
* Usual operations
    + Scale
    + Rotate
    + Translate
    + Shear
    + Flip/Mirror
* Matrices are used extensively in all graphics APIs
    + Can concatenate multiple transforms into one complex transform
* Internalize them by playing with simple "Hello, World" program
* [2D Transforms 101](http://legends2k.github.io/2d-transforms-101/): an auxiliary presentation with interactive animations

# Clipping

# Text
