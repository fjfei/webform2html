<?php
/**
 * @file
 * Webform to HTML settings form.
 */


/**
 * Overview form of all components for this webform.
 */
function webform2html_edit_form($form, &$form_state, $node) {
  $default = webform2html_get_setting($node->nid);

  if (!$default) {
    $default = variable_get('webform2html_default', '');
    $default['enabled'] = 0;
  }

  $form['enabled'] = array(
    '#default_value' => $default['enabled'],
    '#type' => 'checkbox',
    '#title' => t('Generate HTML Document.'),
  );

  $webform2html_default = variable_get('webform2html_default', '');
  // HTML body (page)
  $form['page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content of the HTML document'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
	'#states' => array(
      'visible' => array(
        'input[name="enabled"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['page']['hs_body'] = array(
    '#type' => 'text_format',
    '#base_type' => 'textarea',
    '#title' => t('Page body'),
    '#format' => isset($default['hs_body']['format']) ? $default['hs_body']['format'] : NULL,
    '#rows' => '10',
    '#default_value' => $default['hs_body']['value'],
    '#description' => t("The content of the HTML file can be defined here, the text can be formatted with HTML and CSS tags.")
      . theme('webform_token_help', array('groups' => array('node', 'submission'))),
  );



  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  if (!isset($default['nid'])) {
    $form['new'] = array(
      '#type' => 'value',
      '#value' => 1,
    );
  }
  else {
    $form['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset to defaults'),
    );
  }

  return $form;
} // function webform2html_edit_form()

/*
 * webform2html_edit_form_validate: Implements validate hook
 */
function webform2html_edit_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Save')) {
/*    if (!empty($form_state['values']['h_txt'])) {
      $header = explode('<br />', nl2br( str_replace('<br>', '<br />', $form_state['values']['h_txt']) ) );
      if ( count($header) > 5) {
        form_set_error('h_txt', t('Up to 5 rows can be set!'));
      }
    }

    if (!empty($form_state['values']['f_txt'])) {
      $footer = explode('<br />', nl2br( str_replace('<br>', '<br />', $form_state['values']['f_txt']) ) );
      if ( count($footer) > 2) {
        form_set_error('f_txt', t('Up to 2 rows can be set!'));
      }
    }

    if (!(is_numeric($form_state['values']['h_font_size']) && ($form_state['values']['h_font_size'] > 0))) {
      form_set_error('h_font_size', t('Header font size must be numeric.'));
    }

    if (!(is_numeric($form_state['values']['p_font_size']) && ($form_state['values']['p_font_size'] > 0))) {
      form_set_error('p_font_size', t('Content font size must be numeric.'));
    }

    if (!(is_numeric($form_state['values']['f_font_size']) && ($form_state['values']['f_font_size'] > 0))) {
      form_set_error('f_font_size', t('Footer font size must be numeric.'));
    }
*/
  }
} // function webform2html_edit_form_validate()

/*
 * webform2html_edit_form_submit: Implements submit hook
 */
function webform2html_edit_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Save')) {
    $save = $form_state['values'];
    unset($save['nid']);
    unset($save['enabled']);
    unset($save['submit']);
    unset($save['reset']);
    unset($save['form_build_id']);
    unset($save['form_token']);
    unset($save['form_id']);
    unset($save['op']);

    // First enabled
    if (isset($form_state['values']['new'])) {
      unset($save['new']);

      if ($form_state['values']['enabled']) {
        $w2html_setting['nid'] = $form_state['values']['nid'];
        $w2html_setting['enabled'] = $form_state['values']['enabled'];
        $w2html_setting['data'] = $save;
        drupal_write_record('webform2html', $w2html_setting);
      }
    }
  }
  else {
    // default settings
    $save = variable_get('webform2html_default', '');

  }

  if (!isset($form_state['values']['new'])) {
    // update settings
    $w2html_setting['nid'] = $form_state['values']['nid'];
    $w2html_setting['enabled'] = $form_state['values']['enabled'];
    $w2html_setting['data'] = $save;
    drupal_write_record('webform2html', $w2html_setting, 'nid');
  }
} // function webform2html_edit_form_submit()

