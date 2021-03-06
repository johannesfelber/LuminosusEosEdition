// Copyright (c) 2016 Electronic Theatre Controls, Inc., http://www.etcconnect.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef BPMBLOCK_H
#define BPMBLOCK_H

#include "core/block_data/InOutBlock.h"
#include "utils.h"

#include "core/QCircularBuffer.h"

/**
 * @brief The BpmConstants namespace contains all constants used in BpmBlock.
 */
namespace BpmConstants {
	/**
	 * @brief HISTORY_LENGTH is the length of the beat duration history to evaluate
	 */
    static const int HISTORY_LENGTH = 7;

	/**
	 * @brief MIN_BPM is the minimum expected BPM rate
	 */
	static const int MIN_BPM = 60;
	/**
	 * @brief MAX_BPM is the maximum expected BPM rate
	 */
	static const int MAX_BPM = 160;
}


class BpmBlock : public InOutBlock
{
	Q_OBJECT

    Q_PROPERTY(double bpm READ getBpm WRITE setBpm NOTIFY bpmChanged)
    Q_PROPERTY(double factor READ getFactor WRITE setFactor NOTIFY factorChanged)

public:

	static BlockInfo info() {
		static BlockInfo info;
        info.typeName = "BPM";
        info.nameInUi = "Tap BPM";
        info.category << "Sound2Light";
        info.helpText = "The Beats Per Minute (BPM) value can either be provided by tapping on the "
                        "block, connecting a beat to the input or setting it manually in the block "
                        "settings.\n\n"
                        "Useful to control the speed of the Eos Effect or Speed Master block and "
                        "to set the tempo of generator blocks.\n\n"
                        "Can also be used in connection with the OSC Out Block, where the sequence "
                        "'<bpm>' in its path is replaced by the BPM value.";
        info.qmlFile = "qrc:/qml/Blocks/Audio/BpmBlock.qml";
		info.complete<BpmBlock>();
		return info;
	}

	explicit BpmBlock(MainController* controller, QString uid);

	virtual void getAdditionalState(QJsonObject& state) const override;
	virtual void setAdditionalState(const QJsonObject& state) override;

signals:
	void bpmChanged();
    void factorChanged();

public slots:
	virtual BlockInfo getBlockInfo() const override { return info(); }

    void triggerBeat();
    void updateOutput();

    double getBpm() const { return m_bpm; }
    void setBpm(double value);

    double getFactor() const { return m_factor; }
    void setFactor(double value);

private:
	void updateBpm();

private slots:
	void onInputChanged();

protected:
	/**
	 * @brief m_bpm current detected BPM value
	 */
    double			m_bpm;
	/**
     * @brief m_startTime stores the time when this block was created
	 */
    HighResTime::time_point_t	m_startTime;
	/**
	 * @brief m_lastBeats stores the times of the last beats in seconds since start
	 */
    Qt3DCore::QCircularBuffer<double> m_lastBeats;
	/**
	 * @brief m_lastValue stores the last input value
	 */
	double			m_lastValue;

    double m_factor;
};

#endif // BPMBLOCK_H
