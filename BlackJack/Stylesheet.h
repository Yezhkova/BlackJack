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
                        "font-size:20px; "
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
