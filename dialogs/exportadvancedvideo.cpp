#include "exportadvancedvideo.h"

#include <QGridLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>

#include "dialogs/exportdialog.h"

extern "C" {
	#include <libavcodec/avcodec.h>
}

ExportAdvancedVideo::ExportAdvancedVideo(ExportDialog *parent, int vcodec) :
	QDialog(parent),
	ed(parent)
{
	setWindowTitle("Advanced Video Settings");

	QVBoxLayout* layout = new QVBoxLayout();
	setLayout(layout);

	if (vcodec == AV_CODEC_ID_H264) {
		QHBoxLayout* encoder_layout = new QHBoxLayout();
		encoder_layout->addWidget(new QLabel("Encoder:"));

		h264encoder = new QComboBox();
		h264encoder->addItem("x264 (Software)", H264_ENC_X264);
		h264encoder->addItem("QSV", H264_ENC_QSV);
		//h264encoder->addItem("VAAPI");
		//h264encoder->addItem("NVENC");
		connect(h264encoder, SIGNAL(currentIndexChanged(int)), this, SLOT(h264_encoder_change()));
		encoder_layout->addWidget(h264encoder);

		layout->addLayout(encoder_layout);

		x264_settings_widget = new QWidget();
		QGridLayout* x264_settings = new QGridLayout();
		x264_settings->setMargin(0);
		x264_settings->setSpacing(0);
		x264_settings_widget->setLayout(x264_settings);

		x264_preset_label = new QLabel("Preset:");
		x264_settings->addWidget(x264_preset_label, 0, 0);

		x264preset = new QComboBox();
		x264preset->addItem("ultrafast");
		x264preset->addItem("superfast");
		x264preset->addItem("veryfast");
		x264preset->addItem("faster");
		x264preset->addItem("fast");
		x264preset->addItem("medium");
		x264preset->addItem("slow");
		x264preset->addItem("slower");
		x264preset->addItem("veryslow");
		x264preset->setCurrentText(parent->x264_preset);
		x264_settings->addWidget(x264preset, 0, 1);

		x264_opencl_lookahead = new QCheckBox("OpenCL Lookahead");
		x264_settings->addWidget(x264_opencl_lookahead, 1, 0, 1, 2);
		x264_opencl_lookahead->setChecked(ed->x264_opencl_lookahead);

		layout->addWidget(x264_settings_widget);

		for (int i=0;i<h264encoder->count();i++) {
			if (h264encoder->itemData(i).toInt() == ed->h264_encoder) {
				h264encoder->setCurrentIndex(i);
				break;
			}
		}
	}

	QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	buttons->setCenterButtons(true);
	layout->addWidget(buttons);
	connect(buttons, SIGNAL(accepted()), this, SLOT(save()));
	connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
}

void ExportAdvancedVideo::save() {
	ed->x264_preset = x264preset->currentText();
	ed->x264_opencl_lookahead = x264_opencl_lookahead->isChecked();
	ed->h264_encoder = h264encoder->currentData().toInt();
	accept();
}

void ExportAdvancedVideo::h264_encoder_change() {
	int current_encoder = h264encoder->currentData().toInt();
	x264_settings_widget->setVisible(current_encoder == H264_ENC_X264);
//	x264_settings_widget->setVisible(current_encoder == H264_ENC_QSV);
}
