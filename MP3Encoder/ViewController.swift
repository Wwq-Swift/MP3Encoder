//
//  ViewController.swift
//  MP3Encoder
//
//  Created by kris.wang on 2020/4/29.
//  Copyright © 2020 kris.wang. All rights reserved.
//

import UIKit
import SwiftCpp


class ViewController: UIViewController {
    
    

    override func viewDidLoad() {
        super.viewDidLoad()
        view.backgroundColor = .red
        let btn = UIButton(frame: CGRect(x: 100, y: 100, width: 100, height: 100))
        btn.backgroundColor = .blue
        btn.addTarget(self, action: #selector(startEncode), for: .touchUpInside)
        view.addSubview(btn)
    }
    
    @objc func btnTap() {
        print("sdf")
    }

    @objc func startEncode() {
        let encoder = Mp3Encoder_init()
        var pcmFilePath = CommonUtil.bunldePath(fileName: "vocal.pcm")

////            .cString(using: String.Encoding.utf8) ?? []).description
        var mp3FilePath = CommonUtil.documentPath(fileName: "vocal.mp3")
////            .cString(using: String.Encoding.utf8) ?? []
        let sampleRate: Int = 44100
        let channels: Int = 2
        let bitRate: Int = 128 * 1024
        WQMp3Encoderinit(encoder, pcmFilePath, mp3FilePath, Int32(sampleRate), Int32(channels), Int32(bitRate));
        Mp3Encoder_Encode(encoder);
        Mp3Encoder_Destory(encoder);
    }

}

class CommonUtil {
    class func bunldePath(fileName: String) -> String {
        return Bundle.main.bundlePath + "/" + fileName
    }
    
    class func documentPath(fileName: String) -> String {
        let paths = NSSearchPathForDirectoriesInDomains(FileManager.SearchPathDirectory.documentDirectory, FileManager.SearchPathDomainMask.userDomainMask, true)
        let documentsDirectory = paths.first ?? ""
        return documentsDirectory + "/" + fileName
    }
}

