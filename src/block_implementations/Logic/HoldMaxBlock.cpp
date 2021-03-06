#include "HoldMaxBlock.h"

#include "core/Nodes.h"


HoldMaxBlock::HoldMaxBlock(MainController* controller, QString uid)
	: InOutBlock(controller, uid)
	, m_recentMaxValue(0.0)
	, m_holdTime(1.0)
{
	// prepare Timers:
	m_holdTimer.setSingleShot(true);
	connect(&m_holdTimer, SIGNAL(timeout()), this, SLOT(onHoldTimeEnd()));

	connect(m_inputNode, SIGNAL(dataChanged()), this, SLOT(onInputChanged()));
}

void HoldMaxBlock::getAdditionalState(QJsonObject& state) const {
    state["holdTime"] = getHoldTime();
}

void HoldMaxBlock::setAdditionalState(const QJsonObject &state) {
	setHoldTime(state["holdTime"].toDouble());
}

void HoldMaxBlock::onInputChanged() {
    double value = m_inputNode->getValue();
	if (value > m_recentMaxValue) {
		m_recentMaxValue = value;
	} else {
		if (!m_holdTimer.isActive()) {
			m_holdTimer.start(m_holdTime * 1000);
		}
	}
	m_outputNode->setValue(m_recentMaxValue);
}

void HoldMaxBlock::onHoldTimeEnd() {
    m_recentMaxValue = m_inputNode->getValue();
	m_outputNode->setValue(m_recentMaxValue);
}
