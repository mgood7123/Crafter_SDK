//
// Created by Matthew Good on 12/6/21.
//

#ifndef CRAFTER_POLYGONBLUEPRINT_H
#define CRAFTER_POLYGONBLUEPRINT_H

namespace PolygonDeformer {
    class Blueprint {
    private:
        int polygonResolution;

    public:
        void setPolygonResolution(int polygonResolution);
        int getPolygonResolution();
        void draw();
    };
}


#endif //CRAFTER_POLYGONBLUEPRINT_H
