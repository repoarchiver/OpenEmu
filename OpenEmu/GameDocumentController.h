/*
 Copyright (c) 2009, OpenEmu Team
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
     * Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
     * Neither the name of the OpenEmu Team nor the
       names of its contributors may be used to endorse or promote products
       derived from this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY OpenEmu Team ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL OpenEmu Team BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#import <Cocoa/Cocoa.h>
#import <Quartz/Quartz.h>
#import <IOKit/hid/IOHIDLib.h>
#import <IOKit/hid/IOHIDUsageTables.h>
#import "OEHIDDeviceHandler.h"
#import "OEROMOrganizer.h"
#import "OEVersionMigrationController.h"

@class GameCore, OECorePlugin;
@class GameDocument, OEGamePreferenceController, OESaveStateController, OECoreDownloader;

@interface GameDocumentController : NSDocumentController
{
    GameDocument               *currentGame;
    OEGamePreferenceController *preferences;
    OESaveStateController      *saveStateManager;

    OECoreDownloader		   *coreDownloader;	
	NSArray                    *filterNames;
    NSArray                    *plugins;
    NSArray                    *validExtensions;
    BOOL                        gameLoaded;
    
    IOHIDManagerRef             hidManager;
    NSMutableArray             *deviceHandlers;
    
    // added vade
    IBOutlet NSWindow          *aboutWindow;
    NSString                   *aboutCreditsPath;
    
    // for new QC Composition based filters.
    // the key will be our filter name from the QC Composition attributes or if that is missing, the filename.
    // the value will of course be our QC Composition filter.
    // this will be passed into our QCRenderer in our CALayer where renderForTime will be called.
    NSMutableDictionary* filterDictionary; 
    
    // Core data controller info, used for savestates right now
    
    NSPersistentStoreCoordinator *persistentStoreCoordinator;
    NSManagedObjectModel *managedObjectModel;
    NSManagedObjectContext *managedObjectContext;
	
	OEROMOrganizer *organizer;
	
	OEVersionMigrationController *versionMigrator;
}

@property(readonly) NSArray *filterNames;
@property(readonly, retain) NSArray *plugins;
@property(readwrite) BOOL gameLoaded;
@property(readonly) NSString* appVersion;
@property(readonly) NSAttributedString* projectURL;
@property(readonly) NSString* aboutCreditsPath;
@property(readonly) GameDocument *currentDocument;

@property(readwrite, retain) NSMutableDictionary* filterDictionary;


- (NSString *)applicationSupportFolder;

- (NSPersistentStoreCoordinator *)persistentStoreCoordinator;
- (NSManagedObjectModel *)managedObjectModel;
- (NSManagedObjectContext *)managedObjectContext;

- (NSString *)applicationSupportFolder;

- (OECorePlugin *)pluginForExtension:(NSString *)anExtensions;
- (NSArray *)pluginsForExtension:(NSString *)anExtensions;
- (void)updateFilterNames;
- (void)updateValidExtensions;
- (void)updateInfoPlist;

- (IBAction)updateBundles:(id)sender;
- (BOOL)isGameKey;

- (void)restartApplication;

- (IBAction)saveState:(id)sender;
- (void)loadState:(NSArray*)states;
- (IBAction)openPreferenceWindow:(id)sender;
- (IBAction)openAboutWindow:(id)sender;
- (IBAction)openSaveStateWindow:(id)sender;
- (IBAction)openCoreDownloaderWindow:(id)sender;

- (IBAction)volumeUp:(id)sender;
- (IBAction)volumeDown:(id)sender;

- (IBAction)stopAllEmulators:(id)sender;

- (BOOL)migrateSaveStatesWithError:(NSError **)err;
- (BOOL)removeFrameworkFromLibraryWithError:(NSError **)err;
@end