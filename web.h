const char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>


<head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
	<title>Điều khiển thiết bị</title>
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<style>
		* {
			padding: 0;
			margin: 0 auto;
			font-family: Roboto, sans-serif;
			flex-wrap: wrap;
		}

		.container {
			width: 980px;
			height: 0 auto;
		}

		body {
			background: linear-gradient(to bottom, #33ff81, #1ba57c);
			animation-name: bg;
			animation-duration: 10s;
			animation-timing-function: ease;
			animation-iteration-count: infinite;
			animation-direction: alternate;
		}

		@keyframes bg {
			from {
				background-position: 0 0;
			}

			to {
				background-position: 100% 100%;
			}
		}

		header {
			width: 900px;
			height: 200px;
			/*background-color: aqua;
			*/
		}

		header a {
			float: left;
			width: 30%;
			padding-top: 0;
			width: 50;
			height: 50;
		}

		header div h1 {
			float: right;
			width: 70%;
			text-align: center;
			padding-top: 50px;
		}

		h1 {

			margin-top: 15px;
			/* background-color: aquamarine; */
		}

		.b {
			width: 100px;
			height: 40px;
			font-size: 21px;
			color: #FFF;
			background-color: #4caf50;
			border-radius: 10px;
			flex-wrap: wrap;
		}

		.t {
			width: 100px;
			height: 40px;
			font-size: 21px;
			color: #FFF;
			background-color: #f44336;
			border-radius: 10px;
			flex-wrap: wrap;
		}

		.tt {
			width: 100px;
			height: 40px;
			font-size: 21px;
			color: #0f0e0e;
			background-color: #FFF;
			border-radius: 10px;
			flex-wrap: wrap;
		}

		.my-table1 tr {
			display: inline-block;
			width: 13%;
		}

		table tr td h2 {
			padding-left: 20px;
			width: 300px;

		}

		.my-table td:nth-child(2) {
			/* background-color: #ddd; */
			padding-left: 20px;
			width: 300px;
			height: 100px;
			table-layout: fixed;
		}

		.my-img {
			width: 100px;
			height: 100px;
		}

		.row1 {
			display: inline-block;
		}

		.row2 {
			padding: 2px;
			display: inline-block;
		}
	</style>
</head>
<script>
	function UpdateData() {
		var xhttp = new XMLHttpRequest();
		xhttp.onreadystatechange = function () {
			if (this.readyState == 4 && this.status == 200) {
				var DataVDK = xhttp.responseText;
				console.log("du lieu VDK:" + DataVDK);

				var DataJson = JSON.parse(DataVDK);

				if (DataJson.MN != null) {
					document.getElementById("mucnuoc").innerHTML = DataJson.MN;
				}
				if (DataJson.ND != null) {
					document.getElementById("nhietdo").innerHTML = DataJson.ND;
				}
				if (DataJson.DA != null) {
					document.getElementById("doam").innerHTML = DataJson.DA;
				}

			
				 if (DataJson.TTL != null)
         {
				
					if (DataJson.TTL = 1)
					{
						document.getElementById("ttl").innerHTML = "ON";
					}
					else
					{
						document.getElementById("ttl").innerHTML = "OFF";
					}
          }
				
          if (DataJson.TTDC != null)
					{
          if (DataJson.TTDC = 1)
					{
						document.getElementById("ttdc").innerHTML = "ON";
						
					}
					else
					{
						document.getElementById("ttdc").innerHTML = "OFF";
						
					}
          }
				
			}
		}
		xhttp.open('GET', '/Update', true);
		xhttp.send();

		setTimeout(function () { UpdateData() }, 2000);
	}
</script>

<body onload="UpdateData()">
	<div class="container">
		<header>
			<a href="#"><img src="https://img.upanh.tv/2023/04/25/logo.png" alt="logo.png"></a>
			
			<div>
				<h1>
					QUẢN LÍ HỆ THỐNG CHĂM SÓC VƯỜN
				</h1>
			</div>

		</header>
		<h2 align="center">
			Môi Trường Xung Quanh
		</h2>
		<table class="my-table">

			<tr>
				<td><img class="my-img" src="https://img.upanh.tv/2023/04/25/imagecfe245388373bd5e.png"
						alt="imagecfe245388373bd5e.png"></td>
				<td>
					<h2>Mực nước đo được:</h2>
				</td>
				<td>
					<h1 class="row1">
						<label id="mucnuoc"></label>


					</h1>
					<h1 class="row2"> cm³ </h1>
				</td>

			</tr>
			<tr>
				<td><img class="my-img" src="https://img.upanh.tv/2023/04/25/image494f3f09dd95fd7e.png"
						alt="image494f3f09dd95fd7e.png"></td>
				<td>
					<h2>Nhiệt độ đo được:</h2>
				</td>
				<td>
					<h1 class="row1">
						<label id="nhietdo"></label>
					</h1>
					<h1 class="row2">
						&deg;C
					</h1>
				</td>
			</tr>
			<tr>
				<td><img class="my-img" src="https://img.upanh.tv/2023/04/25/imagecd8e49ebc0b67dd8.png"
						alt="imagecd8e49ebc0b67dd8.png" border="0"></td>
				<td>
					<h2>Độ ẩm đất đo được:</h2>
				</td>
				<td>
					<h1 class="row1">
						<label id="doam"></label>
					</h1>
					<h1 class="row2">
						%
					</h1>
				</td>
			</tr>
		</table>
		<h2 align="center">Điều khiển thiết bị qua WIFI</h2>
		<table class="my-table1" align="center">
			<tr>
				<td><a href='/bat1'><button class='b'>Bật 1</button></a>
				<td>
				<td><a href='/tat1'><button class='t'>Tắt 1</button></a>
				<td>
			<tr>
			<tr>
				<td><button class='b'>LED</button></a>
				<td>
				<td><button id="ttl" class="tt"></button></a>
				<td>
			<tr>
			<tr>
				<td><button class='b'>Động cơ</button></a>
				<td>
				<td><button id="ttdc" class="tt"></button></a>
				<td>
			<tr>
			<tr>
				<td><a href='/bat4'><button class='b'>Bật 4</button></a>
				<td>
				<td><a href='/tat4'><button class='t'>Tắt 4</button></a>
				<td>
			<tr>
		</table>
		<!-- </div> -->
	</div>
</body>

</html>

)=====";