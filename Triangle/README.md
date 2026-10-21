Learnt Bresenhams Line Algo to draw proper lines (so much math though but easy if you once understand it).
Included the algo to draw edges of a triangle.
Also learnt Triangle Rasterisation(also math)


**WiredTri**
So, to get a wireframe triangle with customizable pixel thickness on each edge, I went down a bit of a math rabbit hole (with some AI brainstorming—no judging).Here is the intuition behind how it works:
Instead of calculating the exact perpendicular distance from every single pixel to an edge—which would mean doing expensive floating-point divisions inside nested loops—I flipped the math around to compare areas instead:Precompute the thresholds: For each side, I multiplied its edge length by the desired pixel thickness (length * thickness). Geometrically, this represents the maximum "rectangular area" a point is allowed to produce while still being within the stroke width.
Double the sub-areas: For every pixel $P(x, y)$ in the bounding box, I calculated its sub-triangle areas ($\alpha, \beta, \gamma$). Keeping them doubled ($\times 2$) lets us skip halving and stay entirely in fast integer arithmetic.
The border test: First, $P$ must be inside the triangle (meaning $\alpha, \beta, \gamma \ge 0$, so outside pixels don't slip through). If that holds, and any of the three sub-areas is less than or equal to that edge's threshold area, it means the pixel is close enough to the boundary—so we color it!
Anything with all three areas greater than their thresholds gets left uncolored as the hollow center. Pure integer math, zero divisions per pixel, and each edge gets its own independent thickness.
