/*
 * Proland: a procedural landscape rendering library.
 * Website : http://proland.inrialpes.fr/
 * Copyright (c) 2008-2015 INRIA - LJK (CNRS - Grenoble University)
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors 
 * may be used to endorse or promote products derived from this software without 
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/*
 * Proland is distributed under the Berkeley Software Distribution 3 Licence. 
 * For any assistance, feedback and enquiries about training programs, you can check out the 
 * contact page on our website : 
 * http://proland.inrialpes.fr/
 */
/*
 * Main authors: Eric Bruneton, Antoine Begault, Guillaume Piolat.
 */

#ifndef _PROLAND_CPU_TILE_STORAGE_H_
#define _PROLAND_CPU_TILE_STORAGE_H_

#include "proland/producer/TileStorage.h"

namespace proland
{

/**
 * A TileStorage that store tiles on CPU.
 * @ingroup producer
 * @authors Eric Bruneton, Antoine Begault
 *
 * @tparam T the type of each tile pixel component (e.g. char, float, etc).
 */
template<class T>
class CPUTileStorage : public TileStorage
{
public:
    /**
     * A slot managed by a CPUTileStorage.
     */
    class CPUSlot : public Slot
    {
    public:
        /**
         * The data of the tile stored in this slot.
         */
        T* data;

        /**
         * The number of elements in the data array.
         */
        int size;

        /**
         * Creates a new CPUSlot. This constructor creates a new array to store
         * the tile data.
         *
         * @param owner the TileStorage that manages this slot.
         * @param size the number of elements in the data array.
         */
        CPUSlot(TileStorage *owner, int size) : Slot(owner)
        {
            this->data = new T[size];
            this->size = size;
        }

        /**
         * Deletes this CPUSlot. This deletes the #data array.
         */
        virtual ~CPUSlot()
        {
            if (data != NULL) {
                delete[] data;
            }
        }
    };

    /**
     * Creates a new CPUTileStorage.
     *
     * @param tileSize the size in pixels of each (square) tile.
     * @param channels the number of components per pixel of each tile. Each
     *      component is of type T.
     * @param capacity the number of slots managed by this tile storage.
     */
    CPUTileStorage(int tileSize, int channels, int capacity) : TileStorage()
    {
        init(tileSize, channels, capacity);
    }

    /**
     * Deletes this CPUTileStorage.
     */
    virtual ~CPUTileStorage()
    {
    }

    /**
     * Returns the number of components per pixel of each tile. Each component
     * is of type T.
     */
    int getChannels()
    {
        return channels;
    }

protected:
    /**
     * Creates an uninitialized CPUTileStorage.
     */
    CPUTileStorage() : TileStorage()
    {
    }

    /**
     * Initializes this CPUTileStorage.
     *
     * @param tileSize the size in pixels of each (square) tile.
     * @param channels the number of components per pixel of each tile. Each
     *      component is of type T.
     * @param capacity the number of slots managed by this tile storage.
     */
    void init(int tileSize, int channels, int capacity)
    {
        TileStorage::init(tileSize, capacity);
        this->channels = channels;
        int size = tileSize * tileSize * channels;
        for (int i = 0; i < capacity; ++i) {
            freeSlots.push_back(new CPUSlot(this, size));
        }
    }

    void swap(ptr<CPUTileStorage<T> > t)
    {
    }

private:
    /**
     * The number of components per pixel of each tile.
     */
    int channels;
};

}

#endif
