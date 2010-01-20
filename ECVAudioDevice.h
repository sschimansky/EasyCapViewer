/* Copyright (c) 2009, Ben Trask
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * The names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY BEN TRASK ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL BEN TRASK BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
#ifndef ECV_DISABLE_AUDIO
#import <CoreAudio/CoreAudio.h>

extern NSString *const ECVAudioHardwareDevicesDidChangeNotification;

@protocol ECVAudioDeviceDelegate;

@interface ECVAudioDevice : NSObject
{
	@private
	IBOutlet NSObject<ECVAudioDeviceDelegate> *delegate;
	AudioDeviceID _deviceID;
	BOOL _isInput;
	NSString *_name;
	AudioDeviceIOProcID _procID;
}

+ (NSArray *)allDevicesInput:(BOOL)flag;
+ (id)defaultInputDevice;
+ (id)defaultOutputDevice;
+ (id)deviceWithUID:(NSString *)UID input:(BOOL)flag;
+ (id)deviceWithIODevice:(io_service_t)device input:(BOOL)flag;

- (id)initWithDeviceID:(AudioDeviceID)deviceID input:(BOOL)flag;

@property(assign) NSObject<ECVAudioDeviceDelegate> *delegate;
@property(readonly) AudioDeviceID deviceID;
@property(readonly) BOOL isInput;

@property(copy) NSString *name;
@property(readonly) NSArray *streams;

- (BOOL)start;
- (void)stop;

@end

@protocol ECVAudioDeviceDelegate <NSObject>

@optional
- (void)audioDevice:(ECVAudioDevice *)sender didReceiveInput:(AudioBufferList const *)bufferList atTime:(AudioTimeStamp const *)time;
- (void)audioDevice:(ECVAudioDevice *)sender didRequestOutput:(inout AudioBufferList *)bufferList forTime:(AudioTimeStamp const *)time;

@end

@interface ECVAudioStream : NSObject
{
	@private
	AudioStreamID _streamID;
}

- (id)initWithStreamID:(AudioStreamID)streamID;

@property(readonly) AudioStreamID streamID;

- (AudioStreamBasicDescription)basicDescription;

@end
#endif
