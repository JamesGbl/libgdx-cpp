/*
 Copyright 2011 Aevum Software aevum @ aevumlab.com
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 
 @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 */


#import "IosGdxViewController.h"
#import "EAGLView.h"

#include <gdx-cpp/Gdx.hpp>
#import <QuartzCore/QuartzCore.h>

@interface IosGdxViewController ()
@property (nonatomic, retain) EAGLContext *context;
@end

@implementation IosGdxViewController

@synthesize context, displayLink;

- (id) initWithNibName:(NSString* ) nibNameOrNil bundle:(NSBundle*)nibBundleOrNil {
	if (self = [ super initWithNibName:nibNameOrNil bundle:nibBundleOrNil]) {
        if(UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad) {
            self.view = glView = [[EAGLView viewWithFrame: [UIScreen mainScreen].bounds
                             pixelFormat: kEAGLColorFormatRGBA8
                             depthFormat: GL_DEPTH_COMPONENT16_OES
                      preserveBackbuffer: NO
                              sharegroup: nil
                           multiSampling: YES
                            numberOfSamples: 4] retain];
        } else {
            self.view = glView = [[EAGLView viewWithFrame: [UIScreen mainScreen].bounds
                                              pixelFormat: kEAGLColorFormatRGBA8
                                              depthFormat: GL_DEPTH_COMPONENT16_OES
                                       preserveBackbuffer: NO
                                               sharegroup: nil
                                            multiSampling: NO
                                          numberOfSamples: 0] retain];
        }
	}
	return self;
}

- (void) loadView {
	
}

- (void) viewDidLoad {
	[super viewDidLoad];
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation) interfaceOrientation {
	return UIInterfaceOrientationIsPortrait(interfaceOrientation);
}

- (void) didReceiveMemoryWarning {
	[super didReceiveMemoryWarning];
}

- (void) viewDidUnload {
	[super viewDidUnload];
}

- (void) dealloc {
	if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
    
    [context release];
    [glView release];
    
    [super dealloc];
}

- (void) resume {
	if (!isRunning) {
		CADisplayLink *aDisplayLink = [[UIScreen mainScreen] displayLinkWithTarget:self selector:@selector(mainLoop)];
		[aDisplayLink setFrameInterval:1];
		[aDisplayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
		self.displayLink = aDisplayLink;
        isRunning = TRUE;
	}
}

- (void) pause {
	if (isRunning)
    {
        [self.displayLink invalidate];
        self.displayLink = nil;
        isRunning = FALSE;
    }
}

- (void) mainLoop {   
	[glView setFramebuffer];
	gdx::app->update();
	[glView presentFramebuffer];
}

@end