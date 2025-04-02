// C++ implementation of QSwitch, based off IOS switch, originally prototyped with PySide6
#include "Include/QSwitch.h"
namespace QModern
{
    QSwitch::QSwitch(QWidget *parent, int height)
        : QCheckBox{parent}
    {
        // Check if the height is odd, if so make it even
        if (height % 2 != 0)
            height += 1;

        // Variable intitalization
        m_parent = parent; // set parent for use later, if needed
        m_widgetSize = QSize(height * 2, height); // width, height
        m_knobPadding = m_widgetSize.height()/4; // Widget padding based on height/4
        m_widgetBounds = QRect(QPoint(0, 0), m_widgetSize); // bounds of the widget

        m_activeColor = QColor(52, 198, 89);
        m_backgroundColor = QColor(200, 200, 200);
        m_knobColor = QColor(255, 255, 255);

        // Initial logic
        setMouseTracking(true); // Enable mouse tracking for hover events
        setFixedSize(m_widgetSize); // set the itital size of the widget
    }
    QSwitch::~QSwitch()
    {
        // Free up pointers on deconstruction
        delete m_parent;
    }

    //
    // Event Overloads
    //
    void QSwitch::mousePressEvent(QMouseEvent *event)
    {
        if(event->button() == Qt::LeftButton)
            if(m_widgetBounds.contains(event->pos()))
                toggle();

        qInfo() << "Switch State: " << isChecked();
    }

    void QSwitch::mouseMoveEvent(QMouseEvent *event)
    {
        if (m_widgetBounds.contains(event->pos()))
            setCursor(Qt::PointingHandCursor);
        else
            unsetCursor();
    }

    void QSwitch::paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing); // Set antialiasing
        p.setPen(Qt::transparent);

        // Draw the switch background
        if (isChecked())
            p.setBrush(m_activeColor);
        else
            p.setBrush(m_backgroundColor);

        p.drawRoundedRect(m_widgetBounds, m_widgetSize.height()/2, m_widgetSize.height()/2);

        // Draw the knob
        if (isChecked())
        {
            p.setPen(Qt::transparent);
            p.setBrush(m_knobColor);
            p.drawEllipse((m_widgetSize.width() - m_widgetSize.height()) + m_knobPadding/2,
                          m_knobPadding/2,
                          m_widgetSize.height() - m_knobPadding,
                          m_widgetSize.height() - m_knobPadding);
        }
        else
        {
            p.setPen(Qt::transparent);
            p.setBrush(m_knobColor);
            p.drawEllipse(m_knobPadding/2,
                          m_knobPadding/2,
                          m_widgetSize.height() - m_knobPadding,
                          m_widgetSize.height() - m_knobPadding);
        }
    }

    //
    // Public methods
    //
    QWidget *QSwitch::getParent() const
    {
        return m_parent;
    }

    void QSwitch::enableDropShadow(bool newState)
    {
        m_hasDropShadow = newState;
    }
    void QSwitch::setHeight(int newHeight)
    {
        // Check if newHeight is odd number, if so then +1 to it for future calculations
        if(newHeight % 2 != 0)
            newHeight += 1;

        // update the variables associated with the size calculations
        m_widgetSize = QSize(newHeight * 2, newHeight);
        m_widgetBounds = QRect(QPoint(0, 0), m_widgetSize);

        setFixedSize(m_widgetSize);
        _repaintWidget();
    }

    //
    // Private methods
    //
    void QSwitch::_repaintWidget()
    {
        // method to update and repaint the widget
        update();
        repaint();
    }

    //
    // Property definitions
    //

    // Public
    void QSwitch::setActiveColor(QColor newColor)
    {
        m_activeColor = newColor;
        _repaintWidget();
    }

    void QSwitch::setBackgroundColor(QColor newColor)
    {
        m_backgroundColor = newColor;
    }

    void QSwitch::setKnobColor(QColor newColor)
    {
        m_knobColor = newColor;
    }

    // Private
    QColor QSwitch::_getActiveColor() const
    {
        return m_activeColor;
    }

    QColor QSwitch::_getBackgroundColor() const
    {
        return m_backgroundColor;
    }

    QColor QSwitch::_getKnobColor() const
    {
        return m_knobColor;
    }
}
