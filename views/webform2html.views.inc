<?php

/**
 * @file
 * Views hooks implemented for the Webform2html module.
 */

/**
 * Implements hook_views_data_alter().
 */
function webform2html_views_data_alter(&$data){
  // View submission link.
  $data['webform_submissions']['htmlshow'] = array(
    'title' => t('HTML Show'),
    'help' => t('Only HTML Show.'),
    'real field' => 'serial',
    'field' => array(
      'handler' => 'webform2html_handler_field_submission_htmlshow',
      'click sortable' => TRUE,
      'real field' => 'sid',
      'link_type' => 'html show',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
}

/**
 * Implements hook_views_default_views_alter().
 */
function webform2html_views_default_views_alter(&$views) {
  if (isset($views['webform_submissions'])) {
    $handler =& $views['webform_submissions']->display['default']->handler;
    $htmlshow = array(
      'id' => 'htmlshow',
      'table' => 'webform_submissions',
      'field' => 'htmlshow',
      'label' => '',
      'element_label_colon' => FALSE,
      'access_check' => 0,
    );
    $handler->display->display_options['fields']['htmlshow'] = $htmlshow;
    $handler->display->display_options['style_options']['columns']['htmlshow'] = 'view_submission_1';
  }
}