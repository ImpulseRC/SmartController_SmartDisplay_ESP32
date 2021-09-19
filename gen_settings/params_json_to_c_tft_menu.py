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

//-----------------------
// variables and lists
//-----------------------
{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- for  item in value2.settings %}
            {%- if item.tft_menu_visible %}
{{ item.type }} tft_{{ item.var_name }} = {{ item.default }};
    
                {%- if item.smartphone_display_type == "checkbox" %}
TOGGLE(tft_{{ item.var_name }}, tft_{{ item.var_name }}_LIST,"  {{ item.tft_display_name }} ",doNothing,noEvent,noStyle //
    ,VALUE("Off",0,doNothing,noEvent) //
    ,VALUE("On",1,doNothing,noEvent) //
);
                {%- endif %}
            {%- if item.smartphone_display_type | lower == "list" %}
                {%- set list1 = item.list_strings.split('\\n') %}
TOGGLE(tft_{{ item.var_name }}, tft_{{ item.var_name }}_LIST,"  {{ item.tft_display_name }} ",doNothing,noEvent,noStyle //
                {%- for item4 in list1 %}
    ,VALUE("{{ item4 }}", {{ loop.index - 1 }} ,doNothing,noEvent) //
                {%- endfor %}
);
                {%- endif %}
            {%- endif %}
        {%- endfor %}
    {%- endfor %}
{% endfor %}

/* submenus */
{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- set vars = {'foo': False} %}
        {%- for  item in value2.settings %}
            {%- if item.tft_menu_visible | int == 1 %}
                {%- if vars.update({'foo': True}) %} {% endif %}
            {%- endif %}
        {%- endfor %}

        {%- if vars.foo == True %}
MENU(SUBMENU_{{ key2 | replace(" ", "_")}},"  {{ key2 }}",doNothing,noEvent,noStyle //

        {%- for  item in value2.settings %}
                {%- if item.tft_menu_visible %}
                    {%- if item.smartphone_display_type == "checkbox" %}
    ,SUBMENU(tft_{{ item.var_name }}_LIST) //
                    {%- elif item.smartphone_display_type | lower == "list" %}
    ,SUBMENU(tft_{{ item.var_name }}_LIST) //
                    {%- elif item.type | lower == "float" %}
    ,altFIELD(decPlaces<1>::menuField, tft_{{ item.var_name }}, "  {{ item.tft_display_name }} " ," {{ item.tft_unit }}", {{ item.min }}, {{ item.max }}, {{ item.tft_fast_increment }}, {{ item.tft_slow_increment }}, doNothing,anyEvent,noStyle) //
                    {%- elif 'int' in item.type %}
    ,FIELD(tft_{{ item.var_name }},"  {{ item.tft_display_name }} "," {{ item.tft_unit }}", {{ item.min }}, {{ item.max }}, {{ item.tft_fast_increment | int }}, {{ item.tft_slow_increment | int }}, doNothing,noEvent,noStyle) //
                    {%- else %}
                    {%- endif %}
                {%- endif %}
        {%- endfor %}
    ,EXIT("< Back")
);        
        {%- endif %}
    {% endfor %}
{%- endfor %}

//-----------------------
// menu
//-----------------------
MENU(mainMenu,"  Main menu",doNothing,noEvent,noStyle //
    ,SUBMENU(SUBMENU_MANUAL_status) //
{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- set vars = {'foo': False} %}
        {%- for  item in value2.settings %}
            {%- if item.tft_menu_visible | int == 1 %}
                {%- if vars.update({'foo': True}) %} {% endif %}
            {%- endif %}
        {%- endfor %}
            {%- if vars.foo == True %}
    ,SUBMENU(SUBMENU_{{ key2 | replace(" ", "_")}}) //
        {%- endif %}
    {%- endfor %}
{%- endfor %}
    ,SUBMENU(SUBMENU_MANUAL_more) //
    ,OP("< Discard & exit", discard_exit,enterEvent) //
    ,OP("< Save & exit", save_exit,enterEvent) //
);

//-----------------------
// functions
//-----------------------
void settings_menu_init_from_settings() {
{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- for  item in value2.settings %}
            {%- if item.tft_menu_visible %}
    tft_{{ item.var_name }} = TFT_menu_settings->get_{{ item.var_name }}();
            {%- endif %}
        {%- endfor %}
    {%- endfor %}
{% endfor %}
}

void settings_menu_save_to_settings() {
{%- for key, value in parameters.items() %}
    {%- for key2, value2 in value.items() %}
        {%- for  item in value2.settings %}
            {%- if item.tft_menu_visible %}
    TFT_menu_settings->set_{{ item.var_name }}(tft_{{ item.var_name }});
            {%- endif %}
        {%- endfor %}
    {%- endfor %}
{% endfor %}
    TFT_menu_settings->save();
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
    outputFileName = "src\\TFT\\tft_settings_menu_specs_gen.h"
    print("outputFileName H : " + outputFileName)

    # write output to file
    outFile = open(outputFileName,"w")
    outFile.write(result_h)
    outFile.close()
    
    print("done.")
    