COMMONCPPSRC += $(SOURCEDIR)/main.cpp
COMMONCPPSRC += $(SOURCEDIR)/Memory.cpp
COMMONCPPSRC += $(SOURCEDIR)/PliersManager.cpp
COMMONCPPSRC += $(SOURCEDIR)/Pliers.cpp
COMMONCPPSRC += $(SOURCEDIR)/Servo.cpp
COMMONCPPSRC += $(SOURCEDIR)/DxlPliers.cpp
COMMONCPPSRC += $(SOURCEDIR)/Slider.cpp
COMMONCPPSRC += $(SOURCEDIR)/Shell.cpp

COMMONINC += $(SOURCEDIR)

include $(SOURCEDIR)/$(TARGET_TYPE)/target.mk
