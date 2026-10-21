Learnt Bresenhams Line Algo to draw proper lines (so much math though but easy if you once understand it).
Included the algo to draw edges of a triangle.
Also learnt Triangle Rasterisation(also math)


### 📐 Wireframe Triangles with Per-Edge Thickness

To pull off a wireframe triangle with independently adjustable pixel thickness on each side, I did a bit of math exploration (with some AI brainstorming—no judging).

Instead of calculating the exact perpendicular distance from every single pixel to an edge—which would mean expensive floating-point divisions inside nested loops—I flipped the problem around to compare **areas**:

1. **Precompute the Thresholds:** For each side, I multiplied the edge length by its desired thickness (`length * thickness`). Geometrically, this gives the maximum "rectangular area" a point can form while still sitting inside the stroke width.
2. **Double the Sub-Areas ($\alpha, \beta, \gamma$):** For each pixel $P(x, y)$ in the bounding box, I calculated its sub-triangle areas. Keeping them doubled ($\times 2$) skips the $\frac{1}{2}$ factor and lets everything run in pure integer arithmetic.
3. **The Border Check:**
   * First, make sure the point is actually inside the triangle ($\alpha \ge 0, \beta \ge 0, \gamma \ge 0$) so negative exterior values don't create phantom borders.
   * If any sub-area is $\le$ that edge's threshold area, the pixel is close enough to the edge—so we draw it.

Pixels where all three sub-areas exceed their thresholds are left uncolored, cleanly carving out the hollow center. Zero per-pixel divisions, no floating-point overhead, and full control over each edge's width.
