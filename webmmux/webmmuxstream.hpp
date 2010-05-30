// Copyright (c) 2010 The WebM project authors. All Rights Reserved.
//
// Use of this source code is governed by a BSD-style license and patent
// grant that can be found in the LICENSE file in the root of the source
// tree. All contributing project authors may be found in the AUTHORS
// file in the root of the source tree.

#pragma once

namespace WebmMux
{

class Context;

class Stream
{
    Stream(Stream&);
    Stream& operator=(const Stream&);
    
public:

    virtual ~Stream();
    virtual void Final();  //grant last wishes

    virtual void WriteTrackEntry(int tn);

    virtual HRESULT Receive(IMediaSample*) = 0;
    virtual int EndOfStream() = 0;
    virtual void Flush() = 0;
    virtual bool Wait() const = 0;
    
    void SetTrackNumber(int);
    int GetTrackNumber() const;
        
    class Frame
    {
        Frame(const Frame&);
        Frame& operator=(const Frame&);

    protected:
        Frame();
        virtual ~Frame();

    public:
        virtual bool IsKey() const = 0;
        virtual void Write(const Stream&, ULONG cluster_timecode) const;
        virtual ULONG GetTimecode() const = 0;
        virtual const BYTE* GetData() const = 0;
        virtual ULONG GetSize() const = 0;
        virtual void Release();

    };
   
    Context& m_context;

protected:

    explicit Stream(Context&);
    
    typedef __int64 TrackUID_t;    
    static TrackUID_t CreateTrackUID();    

    int m_trackNumber;

    virtual void WriteTrackNumber(int);
    virtual void WriteTrackUID();
    virtual void WriteTrackType() = 0;
    virtual void WriteTrackName();
    virtual void WriteTrackCodecID() = 0;
    virtual void WriteTrackCodecPrivate();
    virtual void WriteTrackCodecName() = 0;
    virtual void WriteTrackSettings();
    
};


}  //end namespace WebmMux