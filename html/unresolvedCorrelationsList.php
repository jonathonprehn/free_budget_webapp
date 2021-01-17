<!-- This page is loaded into resolveCorrelations.php using jQuery's load() function -->
<div class="row">
	<div class="col-12">
		<h5>Unresolved correlations list</h5>
		<table class="table">
		<tr>
			<th></th>
			<th></th>
			<td></th>
		</tr>
		<?php
		$cat_query = "SELECT ".
					"category, ".
					"description ".
					"from budget_categories;";
		$conn = new mysqli("localhost", "free_budget_conn", "badpassword", "free_budget_db");
		if (mysqli_connect_error()) {
			die("Failed to connect to db: " . mysqli_connect_error());
		}
		try {
			$sel = $conn->query($cat_query);
			while($row = $sel->fetch_assoc()) {
				echo "<tr>";

				echo "</tr>";
			}
		} catch(Exception $e) {
			echo "Error getting list of unresolved correlations: " . $e->getMessage();
		}
		?>
		</table>
		
	</div>
</div>

