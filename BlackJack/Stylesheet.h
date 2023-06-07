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
                        "background-color: white;" // Replace with your own checked indicator image
                        "}"
                        "QCheckBox::indicator:unchecked "
                        "{"
                        "background-color: grey" // Replace with your own unchecked indicator image
                        "}";

QString greaterFont = "font-size: 20px; color: white; font-weight: bold;";

QString greaterYellowFont = "font-size: 20px; color: yellow; font-weight: bold;";

QString smallerFont = "font-size: 15px; font-weight: bold;";
