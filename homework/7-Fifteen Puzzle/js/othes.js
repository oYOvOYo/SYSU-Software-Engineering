/**
 * 拼图游戏
 * 李忠
 */
var pintu = function(url){
	var _this = this;
	_this.url = url;
	_this.error = false;
	_this.error_msg = '';
	_this.qukuai_wh = 450;
	_this.row_col = 3;
	_this.box_border_width = 1;
	_this.qu_margin = 10;
	_this.qu_info_height = 50;
	_this.box_kongbai_num = 2;
	_this.click_lock = true;
	_this.click_num = 0;
	_this.move_speed = 100;

	// 初始化
	_this.ini = function(){

		// 创建图片对象
		var img = new Image();
		img.src = _this.url;

		// 错误处理机制
		img.onerror = function(){
			_this.error = true;
			_this.error_msg = _this.url+'文件加载错误';
			_this.check_error();
			return false;
		};

		// 加载图片结束后执行
		img.onload = function(obj){
			return function(){
				// 判断图片大小
				if(img.width<obj.qukuai_wh || img.height<obj.qukuai_wh){
					_this.error = true;
					_this.error_msg = '图片太小';
					_this.check_error();
					return false;
				}else{
					obj.goujian();
				}
			};
		}(_this);

	};

	// 绑定参数
	_this.bind = function(){
		return false;
	};

	// 构建处理
	_this.goujian = function(){

		// 初始化变量
		_this.box_wh = _this.qukuai_wh/_this.row_col;
		_this.quyu_id = 'pintu_'+new Date().getTime();

		_this.quyu_w = 	_this.qukuai_wh*2 + _this.row_col*_this.box_border_width + _this.qu_margin*2;
		_this.quyu_h = 	_this.qukuai_wh + _this.row_col*_this.box_border_width + _this.qu_info_height + _this.qu_margin*2;

		// 算出分图坐标写入数组
		_this.zqArr = new Array();
		for(var i=0,k=0;i<_this.row_col*_this.row_col;i++){

			if(i>0 && i%_this.row_col==0) k++;

			_this.zqArr.push({
				'x':i%_this.row_col * _this.box_wh,
				'y':k*_this.box_wh
			});

			//alert('x:'+_this.zqArr[i].x+',y:'+_this.zqArr[i].y);
		}

		// 打乱
		_this.ranArr = _this.rd(_this.zqArr);

		// 构建
		var html = '';
		html += '<div id="'+_this.quyu_id+'" style="position:fixed;width:'+_this.quyu_w+'px;height:'+_this.quyu_h+'px;left:50%;top:50%;margin-left:-'+parseInt(_this.quyu_w/2)+'px;margin-top:-'+parseInt(_this.quyu_h/2)+'px;border:1px solid #000;background:#FFF;">';
			html += '<div class="header" style="position:absolute;width:90%;height:'+_this.qu_info_height+'px;left:'+_this.qu_margin+'px;line-height:'+_this.qu_info_height+'px;">';
				html += '<span style="font-weight:bold;margin:0 30px;font-size:18px;">拼图游戏</span>';
				html += '计数<span class="click_num">'+_this.click_num+'</span>';
				html += '<button style="margin:0 50px;" onclick="window.location.reload();">重新开始</button>';
				html += 'Author : 李忠 | blog : <a style="color:#999;" href="http://www.qttc.net" target="_blank">www.qttc.net</a>';
				//html += '<span class="info"></span>';
			html +='</div>';

			var wh = _this.qukuai_wh;
			html += '<div class="pintuqu" style="position:absolute;width:'+wh+'px;height:'+wh+'px;border:1px solid #ccc;left:'+(_this.qu_margin-1)+'px;top:'+(_this.qu_info_height+_this.qu_margin-1)+'px;background:#eee;">';

			for(var i=0,k=0;i<_this.row_col*_this.row_col;i++){
				if(i == _this.box_kongbai_num){
					var background = '';
					var pos = {'x':_this.box_wh,'y':_this.box_wh};
					var is_class = 'kongbai';
					var is_cursor = '';
					var z_index = 0;
				}else{
					var background = 'background:url('+_this.url+') -'+_this.zqArr[i].x+'px -'+_this.zqArr[i].y+'px;'
					var index = _this.random(0,_this.ranArr.length-1);
					var pos = _this.ranArr[index];
					_this.ranArr.splice(index,1);
					var is_class = 'box san';
					var is_cursor = 'cursor:pointer;';
					var z_index = 999999;
				}

				html += '<div x='+_this.zqArr[i].x+' y='+_this.zqArr[i].y+' class="'+is_class+'" style="position:absolute;border:1px solid #eee; width:'+_this.box_wh+'px;height:'+_this.box_wh+'px;margin-top:-1px;margin-left:-1px;'+background+'left:'+_this.box_wh+'px;top:'+_this.box_wh+'px;'+is_cursor+'z-index:'+z_index+';" ranx='+pos.x+' rany='+pos.y+'></div>';
			}

			html += '</div>';

			html += '<div class="yuantu" style="position:absolute;width:'+_this.qukuai_wh+'px;height:'+_this.qukuai_wh+'px;background:url('+_this.url+') 0 0 no-repeat;left:'+(_this.qukuai_wh+_this.qu_margin*2-1)+'px;top:'+(_this.qu_info_height+_this.qu_margin-1)+'px;border:1px solid #ccc;">';
				html += '<span style="position:absolute;display:block;width:50px;height:30px;line-height:30px;background:#FFF;text-align:center;left:0;top:0;">原图</span>';
			html += '</div>';
		html += '<div>';

		$('body').css({'margin':0,'padding':0,'background':'#ccc','font-size':'16px','color':'#999'}).append(html);

		_this.san();
	};

	_this.san = function(){
		//alert($('#'+_this.quyu_id+'>div.pintuqu:eq(0)>div.san').length);
		var obj = $('#'+_this.quyu_id+'>div.pintuqu:eq(0)>div.san:eq(0)');

		obj.animate(
			{ 'left':Number(obj.attr('ranx')),'top':Number(obj.attr('rany')) },
			_this.move_speed*3,
			false,
			function(){
				$(this).removeClass('san').removeAttr('ranx').removeAttr('rany');
				if($('#'+_this.quyu_id+'>div.pintuqu:eq(0)>div.san').length>=1){
					_this.san();
				}else{
					// 创建点击动作
					_this.create_click();
				}
			}
		);
	};

	// 点击动作
	_this.create_click = function(){
		$('#'+_this.quyu_id+'>div.pintuqu:eq(0)>div.box').each(function(){

			$(this).get(0).onclick = function(obj){
				return function(){
					if(obj.click_lock) return;

					obj.click_lock = true;

					var div_this = $(this);
					var kongbai_obj = $('#'+obj.quyu_id+'>div.pintuqu:eq(0)>div.kongbai');
					var div_pos = obj.getxy(div_this);
					var kongbai_pos = obj.getxy(kongbai_obj);

					// 打印信息
					//$('#'+obj.quyu_id+'>div.header:eq(0)>span.info').html('x:'+kongbai_pos.x+',y:'+kongbai_pos.y);

					// 判断可以移动到空白区域
					if(div_pos.x==kongbai_pos.x && Math.abs(div_pos.y-kongbai_pos.y)==obj.box_wh){
						kongbai_obj.css('top',div_pos.y);
						div_this.animate({'top':kongbai_pos.y},obj.move_speed,false,function(){
							// 判断是否拼好
							obj.check_pinhao();
						});
					}else if(div_pos.y==kongbai_pos.y && Math.abs(div_pos.x-kongbai_pos.x)==obj.box_wh){

						kongbai_obj.css('left',div_pos.x);
						div_this.animate({'left':kongbai_pos.x},obj.move_speed,false,function(){
							// 判断是否拼好
							obj.check_pinhao();
						});
					}else{
						_this.click_lock = false;
						return false;
					}
				};
			}(_this);
		});

		_this.click_lock = false;
	};

	// 检测是否拼好
	_this.check_pinhao = function(){
		var is_pinhao = true;
		$('#'+_this.quyu_id+'>div.pintuqu:eq(0)>div').each(function(){
			var dq_pos = _this.getxy($(this));
			if( $(this).attr('x')!=dq_pos.x || $(this).attr('y')!=dq_pos.y ){
				is_pinhao = false;
			}
		});

		if(is_pinhao){
			alert('恭喜，您已拼好图');
		}else{
			_this.click_num++;
			$('#'+_this.quyu_id+'>div.header:eq(0)>span.click_num:eq(0)').html(_this.click_num);
			_this.click_lock = false;
		}
	};

	// 获得节点的x与y
	_this.getxy = function(obj){
		return {'x':parseInt(obj.css('left')),'y':parseInt(obj.css('top'))};
	};

	// 随机取数
	_this.random = function(n,m){
		var c = m-n+1;
		return Math.floor(Math.random() * c + n);
	};

	// 打乱数组
	_this.rd = function(arr){
		var tmp = [];

		for(var i=0;i<arr.length;i++){
			if(i!==Math.floor(_this.row_col*_this.row_col/2)){
				tmp.push(arr[i]);
			}
		}

		var randomsort = function(a, b) {
			return Math.random() > .5 ? -1 : 1;
		}

		//tmp.sort(randomsort);
		return tmp;
	};

	// 错误处理
	_this.check_error = function(){
		if(_this.error){
			alert(_this.error_msg);
			return false;
		}

		return true;
	};


	// 初始化
	_this.ini();

	return _this;
};