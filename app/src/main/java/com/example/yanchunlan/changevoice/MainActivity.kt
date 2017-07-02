package com.example.yanchunlan.changevoice

import android.os.Bundle
import android.support.v7.app.AppCompatActivity
import android.view.View
import org.fmod.FMOD

class MainActivity : AppCompatActivity() {

    val path="file:///android_asset/changevoice.mp3"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        if (!FMOD.checkInit())   FMOD.init(this)
    }

    fun clickFix(view : View) {
        when (view.id) {
            R.id.btn_normal -> VoiceUtil.fix(path, VoiceUtil.TYPE_NORMAL)
            R.id.btn_luoli -> VoiceUtil.fix(path, VoiceUtil.TYPE_LOLITA)
            R.id.btn_dashu -> VoiceUtil.fix(path, VoiceUtil.TYPE_UNCLE)
            R.id.btn_jingsong -> VoiceUtil.fix(path, VoiceUtil.TYPE_THRILLER)
            R.id.btn_gaoguai -> VoiceUtil.fix(path, VoiceUtil.TYPE_FUNNY)
            R.id.btn_kongling -> VoiceUtil.fix(path, VoiceUtil.TYPE_ETHEREAL)
        }
    }

    
    override fun onDestroy() {
        super.onDestroy()
        if (FMOD.checkInit()) FMOD.close()
    }
}
