
<div class="row">
	<div class="col-12">
		<h5>Existing categories</h5>
		<table class="table">
		<tr>
			<th>Category Name</th>
			<th>Description</th>
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
				$c0 = $row["category"];
				$c1 = $row["description"];
				echo "<tr>";
				echo "<td>".$c0."</td>";
				echo "<td>".$c1."</td>";
				echo "<td><button class=\"btn btn-info\" type=\"button\" onclick=\"deleteCategory('".$c0."');\">Delete</button></td>";
				echo "</tr>";
			}
		} catch(Exception $e) {
			echo "Error getting categories: " . $e->getMessage();
		}
		?>
		</table>
		
	</div>
</div>

