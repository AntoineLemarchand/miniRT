# miniRT
A 42 project that aims to build a very basic ray tracer using the school homemade library: the minilibx

[![Norminette](https://github.com/AntoineLemarchand/miniRT/actions/workflows/main.yml/badge.svg)](https://github.com/AntoineLemarchand/miniRT/actions/workflows/main.yml)
## Usage
```
./miniRT <filename>.rt
```
The program reads files with a .rt extension which lines follows theses rules:
(All single upcase letter must have one occurence)
**each line is either:**
1. A: Ambient lightning followed by
- an ambient lightning ratio [0.0, 1.0]
- an RGB colored range [uint8],[uint8],[uint8]

2. C: Camera followed by
- the xyz coordinates of the view point [float],[float],[float]
- the 3d normalized orientation vector [float],[float],[float]
- the field of view (FOV) [0, 180]

3. L: Light followed by
- the xyz coordinates of the view point [float],[float],[float]
- the brightness ratio [0.0, 1.0]
- an RGB colored range [uint8],[uint8],[uint8]

4. sp: Sphere
- the xyz coordinates of the view point [float],[float],[float]
- the diameter [float]
- an RGB colored range [uint8],[uint8],[uint8]

5. pl: Plane
- the xyz coordinates of the view point [float],[float],[float]
- the 3d normalized orientation vector [float],[float],[float]
- an RGB colored range [uint8],[uint8],[uint8]

6. cy: Cylinder
- the xyz coordinates of the view point [float],[float],[float]
- the 3d normalized orientation vector [float],[float],[float]
- the diameter [float]
- the height [float]
- an RGB colored range [uint8],[uint8],[uint8]

**file example**
```
A 0.2 255,255,255

C -50,0,20 0,1,.5 70
L -40,0,30 0.7 255,255,255

pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```
script to generate .rt files from .obj ([matboivin](https://github.com/matboivin/minirt_mesh_converter))
