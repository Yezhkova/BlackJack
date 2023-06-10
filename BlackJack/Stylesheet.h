#pragma once

#include <QString>

QString checkBoxStyle = "QCheckBox::indicator"
                        "{ "
                        "width: 20px;"
                        "height: 20px;"
                        "}"
                        "QCheckBox "
                        "{"
                        "spacing: 5px; "
                        "font-size:17px; "
                        "color:white;"
                        "}"
                        "QCheckBox::indicator:checked "
                        "{"
                        "background-color: white;"
                        "}"
                        "QCheckBox::indicator:unchecked "
                        "{"
                        "background-color: grey"
                        "}";

QString greaterFont = "font-size: 20px; color: white; font-weight: bold;";

QString greaterYellowFont = "font-size: 20px; color: yellow; font-weight: bold;";

QString smallerFont = "font-size: 15px; font-weight: bold;";
