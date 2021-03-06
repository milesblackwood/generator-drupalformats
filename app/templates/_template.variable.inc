<?php

/**
 * @file
 * <%= moduleName %>.variable.inc
 */

/**
 * Implements hook_variable_type_info().
 */
function <%= moduleName %>_variable_type_info() {
  $type['instance_id'] = array(
    'title' => t('Instance ID'),
    'options callback' => '<%= moduleName %>_instance_callback_list',
    'type' => 'select',
  );
  $type['width_items'] = array(
    'title' => t('Browser Items'),
    'multiple' => array('width' => t('Width'), 'items' => t('Items')),
    'build callback' => '<%= moduleName %>_variable_build_browser_width',
    'localize' => TRUE,
    'type' => 'multiple',
  );

  return $type;
}

/**
 * Implements hook_variable_group_info().
 */
function <%= moduleName %>_variable_group_info() {
  $groups['<%= moduleName %>'] = array(
    'title' => t('<%= pluginProper %>'),
    'description' => t('Define instance settings for each <%= moduleProper %> instance.'),
    'access' => 'administer <%= moduleName %> settings',
    'path' => array('admin/config/user-interface/<%= moduleName %>'),
  );

  return $groups;
}

/**
 * Call to variable information.
 */
module_load_include('inc','<%= moduleName %>','settings/<%= moduleName %>_variable.instance');

// @TODO Figure out whether needed or not? Probably not.
/**
 * Variable build callback for browser/items.
 */
function <%= moduleName %>_variable_build_browser_width($variable, $options = array()) {
  $index = str_replace('[instance_id]', $variable['index'], $variable['parent']);
  $name = str_replace('[itemwidth_part]', '', $index);

  foreach ($variable['multiple'] as $key => $child) {
    $repeat_name = $name . $key;

    $variable['name'] = $repeat_name;
    $variable['children'][$repeat_name]['title'] = $child;
    $variable['children'][$repeat_name]['index'] = $key;
    $variable['children'][$repeat_name]['type'] = 'number';
    $variable['children'][$repeat_name]['default'] = $variable['default'][$key];

    $variable = variable_build_multiple($variable, $options);
  }

  return $variable;
}
