/*
    RPG Paper Maker Copyright (C) 2017-2022 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "paneltransformations.h"
#include "ui_paneltransformations.h"
#include "rpm.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

PanelTransformations::PanelTransformations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PanelTransformations),
    m_mapElementPosition(nullptr),
    m_drawKind(DrawKind::Translate)
{
    ui->setupUi(this);
}

PanelTransformations::~PanelTransformations()
{
    this->deletePosition();
    delete ui;
}

DrawKind PanelTransformations::drawKind() const
{
    return m_drawKind;
}

void PanelTransformations::setDrawKind(DrawKind drawKind)
{
    m_drawKind = drawKind;
}

// -------------------------------------------------------
//
//  INTERMEDIARY FUNCTIONS
//
// -------------------------------------------------------

AxisKind PanelTransformations::currentAxisKind() const
{
    return static_cast<AxisKind>(ui->tabWidget->currentIndex());
}

// -------------------------------------------------------

void PanelTransformations::initialize(DrawKind drawKind) {
    this->on_positionSelected(nullptr, true);
    ui->panelSubTransformationX->initialize(drawKind, AxisKind::X);
    ui->panelSubTransformationY->initialize(drawKind, AxisKind::Y);
    ui->panelSubTransformationZ->initialize(drawKind, AxisKind::Z);
    connect(ui->panelSubTransformationX, SIGNAL(positionChanged(Position &)),
        this, SLOT(on_positionChangedUI(Position &)));
    connect(ui->panelSubTransformationY, SIGNAL(positionChanged(Position &)),
        this, SLOT(on_positionChangedUI(Position &)));
    connect(ui->panelSubTransformationZ, SIGNAL(positionChanged(Position &)),
        this, SLOT(on_positionChangedUI(Position &)));
}

// -------------------------------------------------------

void PanelTransformations::deletePosition() {
    if (m_mapElementPosition != nullptr) {
        delete m_mapElementPosition;
        m_mapElementPosition = nullptr;
    }
    this->updateText();
}

// -------------------------------------------------------

void PanelTransformations::updateText() {
    ui->labelSelectedObject->setText(m_mapElementPosition == nullptr ?
        RPM::BRACKET_LEFT + RPM::translate(Translations::NONE).toUpper() + RPM
        ::BRACKET_RIGHT + RPM::NEW_LINE + RPM::NEW_LINE + RPM::NEW_LINE + RPM
        ::NEW_LINE : m_mapElementPosition->toString());
}

//-------------------------------------------------

void PanelTransformations::translate(DrawKind drawKind)
{
    ui->labelSelectedObjectTitle->setText(RPM::BRACKET_LEFT + RPM::translate(
        Translations::SELECTED_OBJECT) + RPM::BRACKET_RIGHT);
    QString title;
    switch (drawKind)
    {
    case DrawKind::Translate:
        title = RPM::translate(Translations::TRANSLATION);
        break;
    case DrawKind::Rotate:
        title = RPM::translate(Translations::ROTATION);
        break;
    default:
        break;
    }
    ui->labelRotation->setText(title + RPM::COLON);
    ui->tabWidget->setTabText(0, RPM::translate(Translations::X));
    ui->tabWidget->setTabText(1, RPM::translate(Translations::Y));
    ui->tabWidget->setTabText(2, RPM::translate(Translations::Z));
}

// -------------------------------------------------------
//
//  SLOTS
//
// -------------------------------------------------------

void PanelTransformations::on_positionSelected(Position *p, bool positive) {
    this->deletePosition();
    m_mapElementPosition = p;
    ui->panelSubTransformationX->setMapElementPosition(p);
    ui->panelSubTransformationY->setMapElementPosition(p);
    ui->panelSubTransformationZ->setMapElementPosition(p);
    this->updateText();

    switch (ui->tabWidget->currentIndex()) {
    case 0:
        ui->panelSubTransformationX->updatePositionClick(positive); break;
    case 1:
        ui->panelSubTransformationY->updatePositionClick(positive); break;
    case 2:
        ui->panelSubTransformationZ->updatePositionClick(positive); break;
    }
}

// -------------------------------------------------------

void PanelTransformations::on_positionChangedUI(Position &previousPosition) {
    this->updateText();

    emit positionChanged(*m_mapElementPosition, previousPosition);
}
