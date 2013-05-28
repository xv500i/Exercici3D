
// Source code from Cube Engine Project
// version 2005_08_29
//
//--DELETED means deleted from original version
	//xtraverts: global variable, vertices counter
	//COMMAND macro
	//isoccluded query in rendermodel function
	//rendermodel OUTBORD, simplified
	//delayedload method
//
//--MODIFIED means modified from original version
	//md2::render function do not use lastmillis global variable, it is included as a parameter
	//rendermodel function do not use lastmillis global variable, it is included as a parameter
	//rendermodel uses tex parameter without lookuptexture method

#include <gl/glut.h>
#include "tools.h"
#include "BoundingBox.h"

struct md2_header
{
    int magic;
    int version;
    int skinWidth, skinHeight;
    int frameSize;
    int numSkins, numVertices, numTexcoords;
    int numTriangles, numGlCommands, numFrames;
    int offsetSkins, offsetTexcoords, offsetTriangles;
    int offsetFrames, offsetGlCommands, offsetEnd;
};

struct md2_vertex
{
    uchar vertex[3], lightNormalIndex;
};

struct md2_frame
{
    float      scale[3];
    float      translate[3];
    char       name[16];
    md2_vertex vertices[1];
};

struct md2
{
    int numGlCommands;
    int* glCommands;
    int numTriangles;
    int frameSize;
    int numFrames;
    int numVerts;
    char* frames;
    vec **mverts;
    int displaylist;
    int displaylistverts;
    float maxX;
	float maxZ;
	float maxY;
	float minX;
	float minZ;
	float minY;
	bool paintBoundingBox;
    mapmodelinfo mmi;
    char *loadname;
    int mdlnum;
    bool loaded;

    bool load(char* filename);
    //--MODIFIED void render(vec &light, int numFrame, int range, float x, float y, float z, float yaw, float pitch, float scale, float speed, int snap, int basetime);
	void render(vec &light, int numFrame, int range, float x, float y, float z, float yaw, float pitch, float scale, float speed, int snap, int lastmillis,int basetime);
    void scale(int frame, float scale, int sn);

    md2() : numGlCommands(0), frameSize(0), numFrames(0), displaylist(0), loaded(false), paintBoundingBox(true) {};

    ~md2()
    {
        if(glCommands)
            delete [] glCommands;
        if(frames)
            delete [] frames;
    }
};