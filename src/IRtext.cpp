// Copyright 2019-2021 - David Conran (@crankyoldgit)

/// @file IRtext.cpp
/// @warning If you add or remove an entry in this file, you should run:
///   '../tools/generate_irtext_h.sh' to rebuild the `IRtext.h` file.

#include "IRtext.h"
#ifndef UNIT_TEST
#include <Arduino.h>
#endif  // UNIT_TEST
#include "IRremoteESP8266.h"
#include "i18n.h"

#ifndef PROGMEM
#define PROGMEM  // Pretend we have the PROGMEM macro even if we really don't.
#endif

#ifndef FPSTR
#define FPSTR(X) X  // Also pretend we have flash-string helper class cast.
#endif

#define IRTEXT_CONST_BLOB_NAME(NAME)\
    NAME ## Blob

#define IRTEXT_CONST_BLOB_DECL(NAME)\
    const char IRTEXT_CONST_BLOB_NAME(NAME) [] PROGMEM

#define IRTEXT_CONST_BLOB_PTR(NAME)\
    IRTEXT_CONST_PTR(NAME) {\
        IRTEXT_CONST_PTR_CAST(IRTEXT_CONST_BLOB_NAME(NAME)) }

#define IRTEXT_CONST_STRING(NAME, VALUE)\
    static IRTEXT_CONST_BLOB_DECL(NAME) { VALUE };\
    IRTEXT_CONST_PTR(NAME) PROGMEM {\
        IRTEXT_CONST_PTR_CAST(&(IRTEXT_CONST_BLOB_NAME(NAME))[0]) }

// Common
IRTEXT_CONST_STRING(kUnknownStr, D_STR_UNKNOWN);  ///< "Unknown"
IRTEXT_CONST_STRING(kProtocolStr, D_STR_PROTOCOL);  ///< "Protocol"
IRTEXT_CONST_STRING(kPowerStr, D_STR_POWER);  ///< "Power"
IRTEXT_CONST_STRING(kOnStr, D_STR_ON);  ///< "On"
IRTEXT_CONST_STRING(kOffStr, D_STR_OFF);  ///< "Off"
IRTEXT_CONST_STRING(kModeStr, D_STR_MODE);  ///< "Mode"
IRTEXT_CONST_STRING(kToggleStr, D_STR_TOGGLE);  ///< "Toggle"
IRTEXT_CONST_STRING(kTurboStr, D_STR_TURBO);  ///< "Turbo"
IRTEXT_CONST_STRING(kSuperStr, D_STR_SUPER);  ///< "Super"
IRTEXT_CONST_STRING(kSleepStr, D_STR_SLEEP);  ///< "Sleep"
IRTEXT_CONST_STRING(kLightStr, D_STR_LIGHT);  ///< "Light"
IRTEXT_CONST_STRING(kPowerfulStr, D_STR_POWERFUL);  ///< "Powerful"
IRTEXT_CONST_STRING(kQuietStr, D_STR_QUIET);  ///< "Quiet"
IRTEXT_CONST_STRING(kEconoStr, D_STR_ECONO);  ///< "Econo"
IRTEXT_CONST_STRING(kSwingStr, D_STR_SWING);  ///< "Swing"
IRTEXT_CONST_STRING(kSwingHStr, D_STR_SWINGH);  ///< "SwingH"
IRTEXT_CONST_STRING(kSwingVStr, D_STR_SWINGV);  ///< "SwingV"
IRTEXT_CONST_STRING(kBeepStr, D_STR_BEEP);  ///< "Beep"
IRTEXT_CONST_STRING(kZoneFollowStr, D_STR_ZONEFOLLOW);  ///< "Zone Follow"
IRTEXT_CONST_STRING(kFixedStr, D_STR_FIXED);  ///< "Fixed"
IRTEXT_CONST_STRING(kMouldStr, D_STR_MOULD);  ///< "Mould"
IRTEXT_CONST_STRING(kCleanStr, D_STR_CLEAN);  ///< "Clean"
IRTEXT_CONST_STRING(kPurifyStr, D_STR_PURIFY);  ///< "Purify"
IRTEXT_CONST_STRING(kTimerStr, D_STR_TIMER);  ///< "Timer"
IRTEXT_CONST_STRING(kOnTimerStr, D_STR_ONTIMER);  ///< "On Timer"
IRTEXT_CONST_STRING(kOffTimerStr, D_STR_OFFTIMER);  ///< "Off Timer"
IRTEXT_CONST_STRING(kTimerModeStr, D_STR_TIMERMODE);  ///< "Timer Mode"
IRTEXT_CONST_STRING(kClockStr, D_STR_CLOCK);  ///< "Clock"
IRTEXT_CONST_STRING(kCommandStr, D_STR_COMMAND);  ///< "Command"
IRTEXT_CONST_STRING(kXFanStr, D_STR_XFAN);  ///< "XFan"
IRTEXT_CONST_STRING(kHealthStr, D_STR_HEALTH);  ///< "Health"
IRTEXT_CONST_STRING(kModelStr, D_STR_MODEL);  ///< "Model"
IRTEXT_CONST_STRING(kTempStr, D_STR_TEMP);  ///< "Temp"
IRTEXT_CONST_STRING(kIFeelStr, D_STR_IFEEL);  ///< "IFeel"
IRTEXT_CONST_STRING(kHumidStr, D_STR_HUMID);  ///< "Humid"
IRTEXT_CONST_STRING(kSaveStr, D_STR_SAVE);  ///< "Save"
IRTEXT_CONST_STRING(kEyeStr, D_STR_EYE);  ///< "Eye"
IRTEXT_CONST_STRING(kFollowStr, D_STR_FOLLOW);  ///< "Follow"
IRTEXT_CONST_STRING(kIonStr, D_STR_ION);  ///< "Ion"
IRTEXT_CONST_STRING(kFreshStr, D_STR_FRESH);  ///< "Fresh"
IRTEXT_CONST_STRING(kHoldStr, D_STR_HOLD);  ///< "Hold"
IRTEXT_CONST_STRING(kButtonStr, D_STR_BUTTON);  ///< "Button"
IRTEXT_CONST_STRING(k8CHeatStr, D_STR_8C_HEAT);  ///< "8C Heat"
IRTEXT_CONST_STRING(k10CHeatStr, D_STR_10C_HEAT);  ///< "10C Heat"
IRTEXT_CONST_STRING(kNightStr, D_STR_NIGHT);  ///< "Night"
IRTEXT_CONST_STRING(kSilentStr, D_STR_SILENT);  ///< "Silent"
IRTEXT_CONST_STRING(kFilterStr, D_STR_FILTER);  ///< "Filter"
IRTEXT_CONST_STRING(k3DStr, D_STR_3D);  ///< "3D"
IRTEXT_CONST_STRING(kCelsiusStr, D_STR_CELSIUS);  ///< "Celsius"
IRTEXT_CONST_STRING(kCelsiusFahrenheitStr, D_STR_CELSIUS_FAHRENHEIT);  ///<
///< "Celsius/Fahrenheit"
IRTEXT_CONST_STRING(kTempUpStr, D_STR_TEMPUP);  ///< "Temp Up"
IRTEXT_CONST_STRING(kTempDownStr, D_STR_TEMPDOWN);  ///< "Temp Down"
IRTEXT_CONST_STRING(kStartStr, D_STR_START);  ///< "Start"
IRTEXT_CONST_STRING(kStopStr, D_STR_STOP);  ///< "Stop"
IRTEXT_CONST_STRING(kMoveStr, D_STR_MOVE);  ///< "Move"
IRTEXT_CONST_STRING(kSetStr, D_STR_SET);  ///< "Set"
IRTEXT_CONST_STRING(kCancelStr, D_STR_CANCEL);  ///< "Cancel"
IRTEXT_CONST_STRING(kUpStr, D_STR_UP);  ///< "Up"
IRTEXT_CONST_STRING(kDownStr, D_STR_DOWN);  ///< "Down"
IRTEXT_CONST_STRING(kChangeStr, D_STR_CHANGE);  ///< "Change"
IRTEXT_CONST_STRING(kComfortStr, D_STR_COMFORT);  ///< "Comfort"
IRTEXT_CONST_STRING(kSensorStr, D_STR_SENSOR);  ///< "Sensor"
IRTEXT_CONST_STRING(kWeeklyTimerStr, D_STR_WEEKLYTIMER);  ///< "WeeklyTimer"
IRTEXT_CONST_STRING(kWifiStr, D_STR_WIFI);  ///< "Wifi"
IRTEXT_CONST_STRING(kLastStr, D_STR_LAST);  ///< "Last"
IRTEXT_CONST_STRING(kFastStr, D_STR_FAST);  ///< "Fast"
IRTEXT_CONST_STRING(kSlowStr, D_STR_SLOW);  ///< "Slow"
IRTEXT_CONST_STRING(kAirFlowStr, D_STR_AIRFLOW);  ///< "Air Flow"
IRTEXT_CONST_STRING(kStepStr, D_STR_STEP);  ///< "Step"
IRTEXT_CONST_STRING(kNAStr, D_STR_NA);  ///< "N/A"
IRTEXT_CONST_STRING(kInsideStr, D_STR_INSIDE);  ///< "Inside"
IRTEXT_CONST_STRING(kOutsideStr, D_STR_OUTSIDE);  ///< "Outside"
IRTEXT_CONST_STRING(kLoudStr, D_STR_LOUD);  ///< "Loud"
IRTEXT_CONST_STRING(kLowerStr, D_STR_LOWER);  ///< "Lower"
IRTEXT_CONST_STRING(kUpperStr, D_STR_UPPER);  ///< "Upper"
IRTEXT_CONST_STRING(kBreezeStr, D_STR_BREEZE);  ///< "Breeze"
IRTEXT_CONST_STRING(kCirculateStr, D_STR_CIRCULATE);  ///< "Circulate"
IRTEXT_CONST_STRING(kCeilingStr, D_STR_CEILING);  ///< "Ceiling"
IRTEXT_CONST_STRING(kWallStr, D_STR_WALL);  ///< "Wall"
IRTEXT_CONST_STRING(kRoomStr, D_STR_ROOM);  ///< "Room"
IRTEXT_CONST_STRING(k6thSenseStr, D_STR_6THSENSE);  ///< "6th Sense"
IRTEXT_CONST_STRING(kTypeStr, D_STR_TYPE);  ///< "Type"
IRTEXT_CONST_STRING(kSpecialStr, D_STR_SPECIAL);  ///< "Special"
IRTEXT_CONST_STRING(kIdStr, D_STR_ID);  ///< "Id" / Device Identifier
IRTEXT_CONST_STRING(kVaneStr, D_STR_VANE);  ///< "Vane"

IRTEXT_CONST_STRING(kAutoStr, D_STR_AUTO);  ///< "Auto"
IRTEXT_CONST_STRING(kAutomaticStr, D_STR_AUTOMATIC);  ///< "Automatic"
IRTEXT_CONST_STRING(kManualStr, D_STR_MANUAL);  ///< "Manual"
IRTEXT_CONST_STRING(kCoolStr, D_STR_COOL);  ///< "Cool"
IRTEXT_CONST_STRING(kHeatStr, D_STR_HEAT);  ///< "Heat"
IRTEXT_CONST_STRING(kDryStr, D_STR_DRY);  ///< "Dry"
IRTEXT_CONST_STRING(kFanStr, D_STR_FAN);  ///< "Fan"
// The following Fans strings with "only" are required to help with
// HomeAssistant & Google Home Climate integration. For compatibility only.
// Ref: https://www.home-assistant.io/integrations/google_assistant/#climate-operation-modes
IRTEXT_CONST_STRING(kFanOnlyStr, D_STR_FANONLY);  ///< "fan-only"
IRTEXT_CONST_STRING(kFan_OnlyStr, D_STR_FAN_ONLY);  ///< "fan_only" (legacy)
IRTEXT_CONST_STRING(kFanOnlyWithSpaceStr, D_STR_FANSPACEONLY);  ///< "Fan Only"
IRTEXT_CONST_STRING(kFanOnlyNoSpaceStr, D_STR_FANONLYNOSPACE);  ///< "FanOnly"

IRTEXT_CONST_STRING(kRecycleStr, D_STR_RECYCLE);  ///< "Recycle"

IRTEXT_CONST_STRING(kMaxStr, D_STR_MAX);  ///< "Max"
IRTEXT_CONST_STRING(kMaximumStr, D_STR_MAXIMUM);  ///< "Maximum"
IRTEXT_CONST_STRING(kMinStr, D_STR_MIN);  ///< "Min"
IRTEXT_CONST_STRING(kMinimumStr, D_STR_MINIMUM);  ///< "Minimum"
IRTEXT_CONST_STRING(kMedStr, D_STR_MED);  ///< "Med"
IRTEXT_CONST_STRING(kMediumStr, D_STR_MEDIUM);  ///< "Medium"

IRTEXT_CONST_STRING(kHighestStr, D_STR_HIGHEST);  ///< "Highest"
IRTEXT_CONST_STRING(kHighStr, D_STR_HIGH);  ///< "High"
IRTEXT_CONST_STRING(kHiStr, D_STR_HI);  ///< "Hi"
IRTEXT_CONST_STRING(kMidStr, D_STR_MID);  ///< "Mid"
IRTEXT_CONST_STRING(kMiddleStr, D_STR_MIDDLE);  ///< "Middle"
IRTEXT_CONST_STRING(kLowStr, D_STR_LOW);  ///< "Low"
IRTEXT_CONST_STRING(kLoStr, D_STR_LO);  ///< "Lo"
IRTEXT_CONST_STRING(kLowestStr, D_STR_LOWEST);  ///< "Lowest"
IRTEXT_CONST_STRING(kMaxRightStr, D_STR_MAXRIGHT);  ///< "Max Right"
IRTEXT_CONST_STRING(kRightMaxStr, D_STR_RIGHTMAX_NOSPACE);  ///< "RightMax"
IRTEXT_CONST_STRING(kRightStr, D_STR_RIGHT);  ///< "Right"
IRTEXT_CONST_STRING(kLeftStr, D_STR_LEFT);  ///< "Left"
IRTEXT_CONST_STRING(kMaxLeftStr, D_STR_MAXLEFT);  ///< "Max Left"
IRTEXT_CONST_STRING(kLeftMaxStr, D_STR_LEFTMAX_NOSPACE);  ///< "LeftMax"
IRTEXT_CONST_STRING(kWideStr, D_STR_WIDE);  ///< "Wide"
IRTEXT_CONST_STRING(kCentreStr, D_STR_CENTRE);  ///< "Centre"
IRTEXT_CONST_STRING(kTopStr, D_STR_TOP);  ///< "Top"
IRTEXT_CONST_STRING(kBottomStr, D_STR_BOTTOM);  ///< "Bottom"

// Compound words/phrases/descriptions from pre-defined words.
IRTEXT_CONST_STRING(kEconoToggleStr, D_STR_ECONOTOGGLE);  ///< "Econo Toggle"
IRTEXT_CONST_STRING(kEyeAutoStr, D_STR_EYEAUTO);  ///< "Eye Auto"
IRTEXT_CONST_STRING(kLightToggleStr, D_STR_LIGHTTOGGLE);  ///< "Light Toggle"
///< "Outside Quiet"
IRTEXT_CONST_STRING(kOutsideQuietStr, D_STR_OUTSIDEQUIET);
IRTEXT_CONST_STRING(kPowerToggleStr, D_STR_POWERTOGGLE);  ///< "Power Toggle"
IRTEXT_CONST_STRING(kPowerButtonStr, D_STR_POWERBUTTON);  ///< "Power Button"
IRTEXT_CONST_STRING(kPreviousPowerStr, D_STR_PREVIOUSPOWER);  ///<
///< "Previous Power"
IRTEXT_CONST_STRING(kDisplayTempStr, D_STR_DISPLAYTEMP);  ///< "Display Temp"
IRTEXT_CONST_STRING(kSensorTempStr, D_STR_SENSORTEMP);  ///< "Sensor Temp"
IRTEXT_CONST_STRING(kSleepTimerStr, D_STR_SLEEP_TIMER);  ///< "Sleep Timer"
IRTEXT_CONST_STRING(kSwingVModeStr, D_STR_SWINGVMODE);  ///< "Swing(V) Mode"
IRTEXT_CONST_STRING(kSwingVToggleStr, D_STR_SWINGVTOGGLE);  ///<
///< "Swing(V) Toggle"
IRTEXT_CONST_STRING(kTurboToggleStr, D_STR_TURBOTOGGLE);  ///< "Turbo Toggle"

// Separators & Punctuation
const char kTimeSep = D_CHR_TIME_SEP;  ///< ':'
IRTEXT_CONST_STRING(kSpaceLBraceStr, D_STR_SPACELBRACE);  ///< " ("
IRTEXT_CONST_STRING(kCommaSpaceStr, D_STR_COMMASPACE);  ///< ", "
IRTEXT_CONST_STRING(kColonSpaceStr, D_STR_COLONSPACE);  ///< ": "
IRTEXT_CONST_STRING(kDashStr, D_STR_DASH);  ///< "-"

// IRutils
//  - Time
IRTEXT_CONST_STRING(kDayStr, D_STR_DAY);  ///< "Day"
IRTEXT_CONST_STRING(kDaysStr, D_STR_DAYS);  ///< "Days"
IRTEXT_CONST_STRING(kHourStr, D_STR_HOUR);  ///< "Hour"
IRTEXT_CONST_STRING(kHoursStr, D_STR_HOURS);  ///< "Hours"
IRTEXT_CONST_STRING(kMinuteStr, D_STR_MINUTE);  ///< "Minute"
IRTEXT_CONST_STRING(kMinutesStr, D_STR_MINUTES);  ///< "Minutes"
IRTEXT_CONST_STRING(kSecondStr, D_STR_SECOND);  ///< "Second"
IRTEXT_CONST_STRING(kSecondsStr, D_STR_SECONDS);  ///< "Seconds"
IRTEXT_CONST_STRING(kNowStr, D_STR_NOW);  ///< "Now"
IRTEXT_CONST_STRING(kThreeLetterDayOfWeekStr, D_STR_THREELETTERDAYS);  ///<
///< "SunMonTueWedThuFriSat"
IRTEXT_CONST_STRING(kYesStr, D_STR_YES);  ///< "Yes"
IRTEXT_CONST_STRING(kNoStr, D_STR_NO);  ///< "No"
IRTEXT_CONST_STRING(kTrueStr, D_STR_TRUE);  ///< "True"
IRTEXT_CONST_STRING(kFalseStr, D_STR_FALSE);  ///< "False"

IRTEXT_CONST_STRING(kRepeatStr, D_STR_REPEAT);  ///< "Repeat"
IRTEXT_CONST_STRING(kCodeStr, D_STR_CODE);  ///< "Code"
IRTEXT_CONST_STRING(kBitsStr, D_STR_BITS);  ///< "Bits"

// Protocol Names
// Needs to be in decode_type_t order.
IRTEXT_CONST_BLOB_DECL(kAllProtocolNamesStr) {
    D_STR_UNUSED "\x0"
    D_STR_RC5 "\x0"
    D_STR_RC6 "\x0"
    D_STR_NEC "\x0"
    D_STR_SONY "\x0"
    D_STR_PANASONIC "\x0"
    D_STR_JVC "\x0"
    D_STR_SAMSUNG "\x0"
    D_STR_WHYNTER "\x0"
    D_STR_AIWA_RC_T501 "\x0"
    D_STR_LG "\x0"
    D_STR_SANYO "\x0"
    D_STR_MITSUBISHI "\x0"
    D_STR_DISH "\x0"
    D_STR_SHARP "\x0"
    D_STR_COOLIX "\x0"
    D_STR_DAIKIN "\x0"
    D_STR_DENON "\x0"
    D_STR_KELVINATOR "\x0"
    D_STR_SHERWOOD "\x0"
    D_STR_MITSUBISHI_AC "\x0"
    D_STR_RCMM "\x0"
    D_STR_SANYO_LC7461 "\x0"
    D_STR_RC5X "\x0"
    D_STR_GREE "\x0"
    D_STR_PRONTO "\x0"
    D_STR_NEC_LIKE "\x0"
    D_STR_ARGO "\x0"
    D_STR_TROTEC "\x0"
    D_STR_NIKAI "\x0"
    D_STR_RAW "\x0"
    D_STR_GLOBALCACHE "\x0"
    D_STR_TOSHIBA_AC "\x0"
    D_STR_FUJITSU_AC "\x0"
    D_STR_MIDEA "\x0"
    D_STR_MAGIQUEST "\x0"
    D_STR_LASERTAG "\x0"
    D_STR_CARRIER_AC "\x0"
    D_STR_HAIER_AC "\x0"
    D_STR_MITSUBISHI2 "\x0"
    D_STR_HITACHI_AC "\x0"
    D_STR_HITACHI_AC1 "\x0"
    D_STR_HITACHI_AC2 "\x0"
    D_STR_GICABLE "\x0"
    D_STR_HAIER_AC_YRW02 "\x0"
    D_STR_WHIRLPOOL_AC "\x0"
    D_STR_SAMSUNG_AC "\x0"
    D_STR_LUTRON "\x0"
    D_STR_ELECTRA_AC "\x0"
    D_STR_PANASONIC_AC "\x0"
    D_STR_PIONEER "\x0"
    D_STR_LG2 "\x0"
    D_STR_MWM "\x0"
    D_STR_DAIKIN2 "\x0"
    D_STR_VESTEL_AC "\x0"
    D_STR_TECO "\x0"
    D_STR_SAMSUNG36 "\x0"
    D_STR_TCL112AC "\x0"
    D_STR_LEGOPF "\x0"
    D_STR_MITSUBISHI_HEAVY_88 "\x0"
    D_STR_MITSUBISHI_HEAVY_152 "\x0"
    D_STR_DAIKIN216 "\x0"
    D_STR_SHARP_AC "\x0"
    D_STR_GOODWEATHER "\x0"
    D_STR_INAX "\x0"
    D_STR_DAIKIN160 "\x0"
    D_STR_NEOCLIMA "\x0"
    D_STR_DAIKIN176 "\x0"
    D_STR_DAIKIN128 "\x0"
    D_STR_AMCOR "\x0"
    D_STR_DAIKIN152 "\x0"
    D_STR_MITSUBISHI136 "\x0"
    D_STR_MITSUBISHI112 "\x0"
    D_STR_HITACHI_AC424 "\x0"
    D_STR_SONY_38K "\x0"
    D_STR_EPSON "\x0"
    D_STR_SYMPHONY "\x0"
    D_STR_HITACHI_AC3 "\x0"
    D_STR_DAIKIN64 "\x0"
    D_STR_AIRWELL "\x0"
    D_STR_DELONGHI_AC "\x0"
    D_STR_DOSHISHA "\x0"
    D_STR_MULTIBRACKETS "\x0"
    D_STR_CARRIER_AC40 "\x0"
    D_STR_CARRIER_AC64 "\x0"
    D_STR_HITACHI_AC344 "\x0"
    D_STR_CORONA_AC "\x0"
    D_STR_MIDEA24 "\x0"
    D_STR_ZEPEAL "\x0"
    D_STR_SANYO_AC "\x0"
    D_STR_VOLTAS "\x0"
    D_STR_METZ "\x0"
    D_STR_TRANSCOLD "\x0"
    D_STR_TECHNIBEL_AC "\x0"
    D_STR_MIRAGE "\x0"
    D_STR_ELITESCREENS "\x0"
    D_STR_PANASONIC_AC32 "\x0"
    D_STR_MILESTAG2 "\x0"
    D_STR_ECOCLIM "\x0"
    D_STR_XMP "\x0"
    D_STR_TRUMA "\x0"
    D_STR_HAIER_AC176 "\x0"
    D_STR_TEKNOPOINT "\x0"
    D_STR_KELON "\x0"
    D_STR_TROTEC_3550 "\x0"
    D_STR_SANYO_AC88 "\x0"
    D_STR_BOSE "\x0"
    D_STR_ARRIS "\x0"
    D_STR_RHOSS "\x0"
    ///< New protocol strings should be added just above this line.
    "\x0"  ///< This string requires double null termination.
};

IRTEXT_CONST_BLOB_PTR(kAllProtocolNamesStr);
