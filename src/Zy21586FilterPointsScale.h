//#pragma once
//#include "DrawingSurface.h"

//class Zy21586FilterPointsScale : public FilterPoints
//{
//public:
//    Zy21586FilterPointsScale(float fFactor, int iWindowX = 720, int iWindowY = 720, FilterPoints* pNextFilter = nullptr)
//        : pNextFilter(pNextFilter)
//    {}
//
//protected:
//    /*
//    This is a bit tricky because if zoomed in we probably need to set a square of pixels instead of a single one.
//    So we use functions to do the x then y loops.
//    */
//    virtual bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
//    {
//        //std::cout << xVirtual << ", " << yVirtual << std::endl;
//        handleXthenY(surface, xVirtual, yVirtual, uiColour);
//        return false; // We already coloured the pixel anyway
//    }
//
//    // Calculate real from virtual Position - apply the stretch then any following filter
//    virtual int filterConvertVirtualToRealXPosition(int xVirtual) override
//    {
//
//        if (pNextFilter)
//            return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual * fFactor);
//        else
//            return xVirtual * fFactor;
//    }
//
//    // Calculate real from virtual Position - apply the stretch then any following filter
//    virtual int filterConvertVirtualToRealYPosition(int yVirtual) override
//    {
//        if (pNextFilter)
//            return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual * fFactor);
//        else
//            return yVirtual * fFactor;
//    }
//
//    // These convert from a clicked location to a virtual pixel Position in a surface
//    virtual int filterConvertRealToVirtualXPosition(int xReal) override
//    {
//        // Apply other filter first if it exists (since we are reversing the order we used for virtual to real)
//        if (pNextFilter)
//            xReal = pNextFilter->filterConvertRealToVirtualXPosition(xReal);
//        // Other filter has now been applied so we can try to reverse the effect of THIS filter...
//        return xReal * fFactor;
//    }
//
//    // These convert from a clicked location to a virtual pixel Position in a surface
//    virtual int filterConvertRealToVirtualYPosition(int yReal) override
//    {
//        // Apply other filter first if it exists (since we are reversing the order we used for virtual to real)
//        if (pNextFilter)
//            yReal = pNextFilter->filterConvertRealToVirtualYPosition(yReal);
//        // Other filter has now been applied so we can try to reverse the effect of THIS filter...
//        return yReal * fFactor;
//    }
//
//
//    /* Set stretch/compress x and y dimensions independently:
//    Positive: Stretch by this factor
//    zero: leave unscaled
//    Negative: Compress by this factor
//    */
//public:
//    void setStretch(float fFactor)
//    {
//        fFactor = fFactor;
//        iNumOfPixelX = fFactor * iWindowX;
//        iNumOfPixelY = fFactor * iWindowY;
//        iCurrentX = 0;
//        iCurrentY = 0;
//        iOffsetX = 0;
//        iOffsetY = 0;
//
//        if (fFactor > 1) {
//            iIntervalX = iWindowX / (iNumOfPixelX - iWindowX);
//            iIntervalY = iWindowY / (iNumOfPixelY - iWindowY);
//        }
//
//        else if (fFactor < 1) {
//            iIntervalX = iWindowX / (iWindowX - iNumOfPixelX) - 1;
//            iIntervalY = iWindowY / (iWindowY - iNumOfPixelY) - 1;
//        }
//    }
//
//
//private:
//    FilterPoints* pNextFilter{ nullptr };
//    float fFactor{ 1.f };
//    int iWindowX{ 720 };
//    int iWindowY{ 720 };
//    int iNumOfPixelX{ 0 };
//    int iNumOfPixelY{ 0 };
//    int iIntervalX{ 0 };
//    int iIntervalY{ 0 };
//    int iCurrentX{ 0 };
//    int iCurrentY{ 0 };
//
//    int iOffsetX{ 0 };
//    int iOffsetY{ 0 };
//
//    void handleXthenY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
//    {
//        if (fFactor > 1) // Stretch it!
//        {
//            xVirtual += iOffsetX;
//            if (++iCurrentX == iIntervalX) {
//                ++iOffsetX;
//                iCurrentX = 0;
//                handleY(surface, xVirtual, yVirtual, uiColour);
//                handleY(surface, xVirtual + 1, yVirtual, uiColour); // colour interpolation
//            }
//            else
//                handleY(surface, xVirtual, yVirtual, uiColour);
//        }
//        else // Shrinking, so just convert the pixel values and skip some
//        {
//            xVirtual += iOffsetX;
//            if (++iCurrentX == iIntervalX) {
//                --iOffsetX;
//                iCurrentX = 0;
//                return;
//            }
//            else
//                handleY(surface, xVirtual, yVirtual, uiColour);
//        }
//
//        if (xVirtual == iWindowX) {
//            iCurrentX = 0;
//            iOffsetX = 0;
//        }
//    }
//
//    void handleY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
//    {
//        if (fFactor > 1) // Stretch it!
//        {
//            yVirtual += iOffsetY;
//            if (++iCurrentY == iIntervalY) {
//                ++iOffsetY;
//                iCurrentY = 0;
//                if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
//                    surface->rawSetPixel(xVirtual, yVirtual, uiColour); // Colour this pixel now
//                if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
//                    surface->rawSetPixel(xVirtual, yVirtual + 1, uiColour); // Colour this pixel now
//            }
//            else
//                if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
//                    surface->rawSetPixel(xVirtual, yVirtual, uiColour); // Colour this pixel 
//        }
//        else
//        {
//            yVirtual += iOffsetY;
//            if (++iCurrentY == iIntervalY) {
//                --iOffsetY;
//                iCurrentY = 0;
//                return;
//            }
//            else
//                if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
//                    surface->rawSetPixel(xVirtual, yVirtual, uiColour); // Colour this pixel now
//        }
//        if (yVirtual == iWindowY) {
//            iCurrentY = 0;
//            iOffsetY = 0;
//        }
//
//    }
//};
//
//
//
//
//
//
//

#pragma once
#include "DrawingSurface.h"

class Zy21586FilterPointsScale : public FilterPoints
{
public:
    Zy21586FilterPointsScale(int xFactor, int yFactor, FilterPoints* pNextFilter = nullptr)
        : pNextFilter(pNextFilter), xStretch(1), yStretch(1), xCompress(1), yCompress(1)
    {
        setStretch(xFactor, yFactor);
    }

protected:
    virtual bool filter(DrawingSurface* surface, int& xVirtual, int& yVirtual, unsigned int& uiColour) override
    {
        handleXthenY(surface, xVirtual, yVirtual, uiColour);
        return false; // We already coloured the pixel anyway
    }

    virtual int filterConvertVirtualToRealXPosition(int xVirtual) override
    {
        if (xStretch > 1)
        {
            if (pNextFilter)
                return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual * xStretch);
            else
                return xVirtual * xStretch;
        }
        else
        {
            if (pNextFilter)
                return pNextFilter->filterConvertVirtualToRealXPosition(xVirtual / xCompress);
            else
                return xVirtual / xCompress;
        }
    }

    virtual int filterConvertVirtualToRealYPosition(int yVirtual) override
    {
        if (yStretch > 1)
        {
            if (pNextFilter)
                return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual * yStretch);
            else
                return yVirtual * yStretch;
        }
        else
        {
            if (pNextFilter)
                return pNextFilter->filterConvertVirtualToRealYPosition(yVirtual / xCompress);
            else
                return yVirtual / yCompress;
        }
    }

    virtual int filterConvertRealToVirtualXPosition(int xReal) override
    {
        // Apply other filter first if it exists (since we are reversing the order we used for virtual to real)
        if (pNextFilter)
            xReal = pNextFilter->filterConvertRealToVirtualXPosition(xReal);
        // Other filter has now been applied so we can try to reverse the effect of THIS filter...
        if (xStretch > 1)
            return xReal / xStretch;
        else
            return xReal * xCompress;
    }

    // These convert from a clicked location to a virtual pixel Position in a surface
    virtual int filterConvertRealToVirtualYPosition(int yReal) override
    {
        // Apply other filter first if it exists (since we are reversing the order we used for virtual to real)
        if (pNextFilter)
            yReal = pNextFilter->filterConvertRealToVirtualYPosition(yReal);
        // Other filter has now been applied so we can try to reverse the effect of THIS filter...
        if (yStretch > 1)
            return yReal / yStretch;
        else
            return yReal * yCompress;
    }
  /*  void stretchX() { if (xCompress > 1) --xCompress; else ++xStretch; }
    void stretchY() { if (yCompress > 1) --yCompress; else ++yStretch; }
    void compressX() { if (xStretch > 1) --xStretch; else ++xCompress; }
    void compressY() { if (yStretch > 1) --yStretch; else ++yCompress; }

    void compress() { compressX(); compressY(); }
    void stretch() { stretchX(); stretchY(); }*/
public:
    void setStretch(int xFactor, int yFactor)
    {
        if (xFactor == 0) { xStretch = 1; xCompress = 1; }
        else if (xFactor < 0) { xStretch = 1; xCompress = 1 - xFactor; }
        else if (xFactor > 0) { xStretch = 1 + xFactor; xCompress = 1; }
        if (yFactor == 0) { yStretch = 1; yCompress = 1; }
        else if (yFactor < 0) { yStretch = 1; yCompress = 1 - yFactor; }
        else if (yFactor > 0) { yStretch = 1 + yFactor; yCompress = 1; }
    }

private:
    FilterPoints* pNextFilter;
    int xStretch;
    int yStretch;
    int xCompress;
    int yCompress;

    void handleXthenY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
    {
        if (xStretch > 1) // Stretch it!
        {
            xVirtual *= xStretch; // First multiply the point coordinates
            for (int i = 0; i < xStretch; i++)
                handleY(surface, xVirtual + i, yVirtual, uiColour);
        }
        else // Shrinking, so just convert the pixel values and skip some
        {
            if ((xVirtual % xCompress) != 0) // We only need the nth pixel drawing now
                return; // Don't draw it
            xVirtual /= xCompress; // Shrink the coordinate by this amount
            handleY(surface, xVirtual, yVirtual, uiColour);
        }
    }

    void handleY(DrawingSurface* surface, int xVirtual, int yVirtual, unsigned int& uiColour)
    {
        if (yStretch > 1) // Stretch it!
        {
            yVirtual *= yStretch; // First multiply the point coordinates
            for (int i = 0; i < yStretch; i++)
            {
                // If no following filter, or filter permits it, then colour the pixel
                int yTest = yVirtual + i; // Need to be able to pass in by reference...
                if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yTest, uiColour))
                    surface->rawSetPixel(xVirtual, yTest, uiColour); // Colour this pixel now
            }
        }
        else
        {
            if ((yVirtual % yCompress) != 0) // We only need the nth pixel drawing now
                return; // Don't draw it
            yVirtual /= yCompress; // Shrink the coordinate by this amount
            if ((pNextFilter == nullptr) || pNextFilter->filter(surface, xVirtual, yVirtual, uiColour))
                surface->rawSetPixel(xVirtual, yVirtual, uiColour); // Colour this pixel now
        }
    }
};
