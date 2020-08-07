//
//  KarteBridge.swift
//  Cocos2dxSample-mobile
//
//  Created by koichi tanaka on 2020/07/15.
//

import Foundation
import KarteCore

class KarteBridge {
}

extension KarteBridge: Library {
    static var name: String {
        "cocos2dx"
    }
    
    static var version: String {
        KRTCocos2dxBridgeCurrentLibraryVersion()
    }
    
    static var isPublic: Bool {
        true
    }
    
    static func configure(app: KarteApp) {
    }
    
    static func unconfigure(app: KarteApp) {
    }
}

extension KarteBridgeLoader {
    open override class func handleLoad() {
        KarteApp.register(library: KarteBridge.self)
    }
}
