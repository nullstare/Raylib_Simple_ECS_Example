## General

Using following struct desing for entity.

```C
struct Entity {
	unsigned int id;
	int type;
	void* data;
	void (*process)( Entity* entity, float delta );
	void (*draw)( Entity* entity );
};
```

<img align="left" src="https://github.com/nullstare/Raylib_Simple_Entity_System/screenshot.png" width="1024px">

## Building

If compiling statically, move libraylib.a to "lib" folder. To build do the usual.

```
mkdir build
cd build
cmake ..
make
```
