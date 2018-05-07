<?php
/**
 * @file
 * Implemented menu path:
 * node/%webform_menu/submission/%webform_menu_submission/html
 */
function webform2html_submission_htmlshow($node, $submission) {
  $template = _webform2html_get_template($node->nid);
//  $template[hs_body];

  $htmlshow = theme('webform2html_content', array('node' => $node, 'submission' => $submission, 'template' => $template));
  return $htmlshow;

}