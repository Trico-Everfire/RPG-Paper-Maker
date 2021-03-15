/*
    RPG Paper Maker Copyright (C) 2017-2021 Wano

    RPG Paper Maker engine is under proprietary license.
    This source code is also copyrighted.

    Use Commercial edition for commercial use of your games.
    See RPG Paper Maker EULA here:
        http://rpg-paper-maker.com/index.php/eula.
*/

#include "systemweapon.h"

// -------------------------------------------------------
//
//  CONSTRUCTOR / DESTRUCTOR / GET / SET
//
// -------------------------------------------------------

SystemWeapon::SystemWeapon() :
    SystemCommonSkillItem()
{

}

SystemWeapon::SystemWeapon(int i, QString name, int pictureID, int type, bool
    oneHand, SystemTranslatable *description, TargetKind targetKind, PrimitiveValue
    *targetConditionFormula, PrimitiveValue *conditionFormula, PrimitiveValue
    *animationUserID, PrimitiveValue *animationTargetID, QStandardItemModel
    *price, QStandardItemModel *modelCosts, QStandardItemModel *modelEffects,
    QStandardItemModel *modelCharacteristics) :
    SystemCommonSkillItem(i, name, pictureID, type, false, oneHand, description,
        targetKind, targetConditionFormula, conditionFormula, AvailableKind::Never,
        new SystemPlaySong(-1, SongKind::Sound), animationUserID,
        animationTargetID, price, modelCosts, modelEffects, modelCharacteristics)
{

}

SystemWeapon::~SystemWeapon() {

}

// -------------------------------------------------------
//
//  VIRTUAL FUNCTIONS
//
// -------------------------------------------------------

void SystemWeapon::read(const QJsonObject &json) {
    SystemCommonSkillItem::read(json);
}

// -------------------------------------------------------

void SystemWeapon::write(QJsonObject &json) const {
    SystemCommonSkillItem::write(json);
}
