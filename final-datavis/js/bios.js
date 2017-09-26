$(document).ready(function() {

	$("div.bio-pics>img").click(function(){

		// remove .active from all
		$("div.bio-pics>img, div.bio-content>div").each(function(){
			$(this).removeClass("active");
		});

		$(this).addClass("active");
		var name = $(this).attr("data");

		$('div.bio-content>div[data=' + name + ']').addClass("active");

	});

});
