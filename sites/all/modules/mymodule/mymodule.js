
function refreshTable(page, sort, order) {
	if(!page) page = 0;
	if(!sort) sort = '';
	if(!order) order = '';

	jQuery.ajax({
		cache: false,
		url: Drupal.settings.basePath + '?q=mymodule/test/pager/callback',
		data: {page: page, sort: sort, order: order},
		dataType: 'text',
		error: function(request, status, error) {
			alert(status);
		},
		success: function(data, status, request) {
			var html = data;

			jQuery('#table-container').html(html);
			
			jQuery('#table-container th a').
				add('#table-container .pager-item a')
				.add('#table-container .pager-first a')
				.add('#table-container .pager-previous a')
				.add('#table-container .pager-next a')
				.add('#table-container .pager-last a')
					.click(function(el, a, b, c) {
						var url = jQuery.url(el.currentTarget.getAttribute('href'));
						refreshTable(url.param('page'), url.param('sort'), url.param('order'));
					
						return (false);
					});
		}
	});
}
	
function initializeTable() {
	jQuery(document).ready(function() {
		refreshTable();
	});
}
