#include "LifeStyle.h"

/**
 * Method which represents the LifeStyle constructor. It takes parameter map<string, vector<tm>> style with all
 * found constants from the database.
 * - Constants:
 *      Breakfast:  from 7:00:00 to 7:30:00
 *      Lunch:      from 12:00:00 to 12:30:00
 *      Snack:      from 16:00:00 to 16:15:00
 *      Dinner:     from 19:00:00 to 19:30:00
 * @param style (map<string, vector<tm>> - key (name of the constant, in vector - start and end time))
 */
LifeStyle::LifeStyle(const map<string, vector<tm>> &style) : style(style) {}
/**
 * Method which represents the getter. It returns the style variable - life style constants.
 * @return map<string, vector<tm>> (style)
 */
map<string, vector<tm>> LifeStyle::getStyle() const { return style; }