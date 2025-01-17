import json
import re
import jinja2

template_h = """
//////------------------------------------
//////------------------------------------
//////------------------------------------
////// GENERATED FILE - DO NOT EDIT MANUALLY
//////------------------------------------
//////------------------------------------
//////------------------------------------

#include <AutoConnect.h>


//-----------------------
// variables and lists
//-----------------------

/* elements */
{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- set outer_loop = loop %}
ACText(ACS{{ outer_loop.index }}, "<h2>{{ key2 }}</h2>", "");
        {%- for  item in value2.settings %}

                {%- if item.smartphone_display_type == "edit_text_number_float" %}
ACInput(ACS{{ outer_loop.index }}_{{ loop.index }}, "{{ item.default }}", "{{ item.tft_display_name }}" {%- if item.regex_valid != "" %}, "{{item.regex_valid}}"{%- endif %}, "", AC_Tag_BR, AC_Input_Text);   
                {%- endif %}
                {%- if item.smartphone_display_type == "edit_text_number_integer" %}
ACInput(ACS{{ outer_loop.index }}_{{ loop.index }}, "{{ item.default }}", "{{ item.tft_display_name }}" {%- if item.regex_valid != "" %}, "{{item.regex_valid}}"{%- endif %}, "", AC_Tag_BR, AC_Input_Text);   
                {%- endif %}
                {%- if item.smartphone_display_type == "edit_text_number_integer_signed" %}
ACInput(ACS{{ outer_loop.index }}_{{ loop.index }}, "{{ item.default }}", "{{ item.tft_display_name }}" {%- if item.regex_valid != "" %}, "{{item.regex_valid}}"{%- endif %}, "", AC_Tag_BR, AC_Input_Text);        
                {%- endif %}
                {%- if item.smartphone_display_type == "edit_text_string" %}
ACInput(ACS{{ outer_loop.index }}_{{ loop.index }}, "{{ item.default }}", "{{ item.tft_display_name }}" {%- if item.regex_valid != "" %}, "{{item.regex_valid}}"{%- endif %}, "", AC_Tag_BR, AC_Input_Text);     
                {%- endif %}
                {%- if item.smartphone_display_type == "edit_text_password" %}
ACInput(ACS{{ outer_loop.index }}_{{ loop.index }}, "{{ item.default }}", "{{ item.tft_display_name }}" {%- if item.regex_valid != "" %}, "{{item.regex_valid}}"{%- endif %}, "", AC_Tag_BR, AC_Input_Password);        
                {%- endif %}
                {%- if item.smartphone_display_type == "seek_bar" %}
ACInput(ACS{{ outer_loop.index }}_{{ loop.index }}, "{{ item.default }}", "{{ item.tft_display_name }}" {%- if item.regex_valid != "" %}, "{{item.regex_valid}}"{% else %}, "" {%- endif %}, "", AC_Tag_BR, AC_Input_Text);  
                {%- endif %}
                {%- if item.smartphone_display_type == "checkbox" %}
ACCheckbox(ACS{{ outer_loop.index }}_{{ loop.index }}, "ACS{{ outer_loop.index }}_{{ loop.index }}", "{{ item.tft_display_name }}", false, AC_Infront);   
                {%- endif %}
                {%- if item.smartphone_display_type | lower == "list" %}
                    {%- set list1 = item.list_strings | replace('\\n', '","') %}
ACSelect(ACS{{ outer_loop.index }}_{{ loop.index }}, {"{{ list1 }}"}, "{{ item.tft_display_name }}", {{ item.default }});
                {%- endif %}
        {%- endfor %}
    {%- endfor %}
{%- endfor %}


/* menus */
AutoConnectAux settingsPageAux("/settingspage", "SmartElec settings", true, {
    ACE_Style1,
    ACE_Style2,
    ACE_Style3,
    ACE_Style4,
{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {% set outer_loop = loop %}
    ACS{{ outer_loop.index }},
        {%- for  item in value2.settings %}
    ACS{{ outer_loop.index }}_{{ loop.index }},
        {%- endfor %}
    {%- endfor %}
{%- endfor %}
    ACE_SETTINGS_Discard, 
    ACE_SETTINGS_Save,
    ACE_SETTINGS_Js1 });        


/* save */
void saveConfig(AutoConnectAux &aux)
{

{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- set outer_loop = loop %}
        {%- for  item in value2.settings %}

                {%- if item.smartphone_display_type == "edit_text_number_float" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectInput>()).value.toFloat());
                {%- elif item.smartphone_display_type == "edit_text_number_integer" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectInput>()).value.toInt());
                {%- elif item.smartphone_display_type == "edit_text_number_integer_signed" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectInput>()).value.toInt());
                {%- elif item.smartphone_display_type == "edit_text_string" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectInput>()).value);
                {%- elif item.smartphone_display_type == "edit_text_password" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectInput>()).value);
                {%- elif item.smartphone_display_type == "seek_bar" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectInput>()).value.toInt());
                {%- elif item.smartphone_display_type == "checkbox" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectCheckbox>()).checked ? 1 : 0);
                {%- elif item.smartphone_display_type | lower == "list" %}
    WifiSettingsPortal_settings->set_{{ item.var_name }}((settingsPageAux["ACS{{ outer_loop.index }}_{{ loop.index }}"].as<AutoConnectSelect>()).selected - 1);
                {%- endif %}
        {%- endfor %}
    {%- endfor %}
{%- endfor %}
    WifiSettingsPortal_settings->save();
    
}

/* load */
void loadConfig(AutoConnectAux &aux)
{

{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- set outer_loop = loop %}
        {%- for  item in value2.settings %}
            {%- set outer_loop1 = loop %}
            {%- if item.smartphone_display_type == "edit_text_number_float" %}
    aux.setElementValue("ACS{{ outer_loop.index }}_{{ loop.index }}", (String)WifiSettingsPortal_settings->get_{{ item.var_name }}());
            {%- elif item.smartphone_display_type == "edit_text_number_integer" %}
    aux.setElementValue("ACS{{ outer_loop.index }}_{{ loop.index }}", (String)WifiSettingsPortal_settings->get_{{ item.var_name }}());
            {%- elif item.smartphone_display_type == "edit_text_number_integer_signed" %}
    aux.setElementValue("ACS{{ outer_loop.index }}_{{ loop.index }}", (String)WifiSettingsPortal_settings->get_{{ item.var_name }}());
            {%- elif item.smartphone_display_type == "edit_text_string" %}
    aux.setElementValue("ACS{{ outer_loop.index }}_{{ loop.index }}", (String)WifiSettingsPortal_settings->get_{{ item.var_name }}());
            {%- elif item.smartphone_display_type == "edit_text_password" %}
    aux.setElementValue("ACS{{ outer_loop.index }}_{{ loop.index }}", (String)WifiSettingsPortal_settings->get_{{ item.var_name }}());
            {%- elif item.smartphone_display_type == "seek_bar" %}
    aux.setElementValue("ACS{{ outer_loop.index }}_{{ loop.index }}", (String)WifiSettingsPortal_settings->get_{{ item.var_name }}());
            {%- elif item.smartphone_display_type == "checkbox" %}
    aux.setElementValue("ACS{{ outer_loop.index }}_{{ loop.index }}", WifiSettingsPortal_settings->get_{{ item.var_name }}() ? "checked" : "");
            {%- elif item.smartphone_display_type | lower == "list" %}
                {%- set list1 = item.list_strings.split('\\n') %}
    uint8_t val_{{ item.var_name }} = WifiSettingsPortal_settings->get_{{ item.var_name }}();
                {%- for item4 in list1 %}
    if (val_{{ item.var_name }} == {{ loop.index - 1 }})
        aux.setElementValue("ACS{{ outer_loop.index }}_{{ outer_loop1.index }}", "{{ item4 }}");
                {%- endfor %}
            {%- endif %}
        {%- endfor %}
    {%- endfor %}
{%- endfor %}

}

"""


# Custom filter method
def regex_replace(s, find, replace):
    """A non-optimal implementation of a regex filter"""
    return re.sub(find, replace, s)

env = jinja2.Environment()
env.filters['regex_replace'] = regex_replace

tmpl_h = env.from_string(template_h)


# load json from file
jsonConfigName = "gen_settings\\params.json"
print ("jsonConfigName: " + jsonConfigName)

with open(jsonConfigName) as json_file:
    json_data = json.load(json_file)

    # merge template with data
    result_h = tmpl_h.render(parameters=json_data)

    # get template name, output file name
    outputFileName = "src\\WifiSettingsPortal\\WifiSettingsPortalSpecs.h"
    print("outputFileName H : " + outputFileName)

    # write output to file
    outFile = open(outputFileName,"w")
    outFile.write(result_h)
    outFile.close()
    
    print("done.")
    