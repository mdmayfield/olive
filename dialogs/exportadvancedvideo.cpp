#include "exportadvancedvideo.h"

#include <QGridLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QComboBox>

#include "dialogs/exportdialog.h"

extern "C" {
	#include <libavcodec/avcodec.h>
}

ExportAdvancedVideo::ExportAdvancedVideo(ExportDialog *parent, int vcodec) :
	QDialog(parent),
	ed(parent)
{
	setWindowTitle("Advanced Video Settings");

	QGridLayout* layout = new QGridLayout();
	setLayout(layout);

	int row = 0;

	if (vcodec == AV_CODEC_ID_H264) {
		layout->addWidget(new QLabel("Encoder:"), row, 0);

		QComboBox* h264encoder = new QComboBox();
		h264encoder->addItem("x264 (Software)");
		h264encoder->addItem("QSV");
		h264encoder->addItem("VAAPI");
		h264encoder->addItem("NVENC");
		layout->addWidget(h264encoder, row, 1);

		row++;

		layout->addWidget(new QLabel("Preset:"), row, 0);

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
		layout->addWidget(x264preset, row, 1);

		row++;
	}

	QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
	buttons->setCenterButtons(true);
	layout->addWidget(buttons, row, 0, 1, 2);
	connect(buttons, SIGNAL(accepted()), this, SLOT(save()));
	connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
}

void ExportAdvancedVideo::save() {
	ed->x264_preset = x264preset->currentText();
	accept();
}
