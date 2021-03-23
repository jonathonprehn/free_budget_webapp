
require "dbi"
require "json"
require "htmlentities"

class AccountingObject

	def initialize
		@accountingType = "generic"
	end

	def fromJSON(json)
		puts "fromJSON not implemented"
	end
	
	def toJSON
		puts "toJSON not implemented"
	end
	
	def dbCommit(sqlConn)
		puts "dbCommit Not implemented"
	end
	
	def fromDB(sqlConn, primaryKey)
		puts "fromDB Not implemented"
	end
	
	def accountingType
		@accountingType
	end
	
	def accountingType=(accountingType)
		@accountingType = accountingType
	end
end



class AccountingLineType < AccountingObject
	def initialize
		@accountingType = "AccountingLineType"
		@lineTypeId = 0
		@lineTypeText = ""
	end

	def fromJSON(json)
		jsonObj = JSON.parse(json, symbolize_names: true)
		@lineTypeId = jsonObj["line-type-id"]
		@lineTypeText = jsonObj["line-type"]
	end
	
	def toJSON
		return "{ \"line-type-id\" : #{@lineTypeId}, \"line-type\": \"#{@lineTypeText}\" }"
	end
	
	def dbCommit(sqlConn)
		# "Cannot commit. Static database object"
		
	end
	
	def fromDB(sqlConn, primaryKey)
		# retrieve the line type by the id 
		# let any database errors bubble up
		prep = sqlConn.prepare("SELECT line_type_description FROM accounting_line_types WHERE line_type_id = #{primaryKey};")
		val = nil
		prep.execute 
		prep.fetch do |row| val = row["line_type_description"] end
		prep.finish
		unless val.nil?  
			@lineTypeId = primaryKey
			@lineTypeText = val.to_s
		else
			puts "No line type with id " << primaryKey
		end
	end
	
	attr_accessor :lineTypeId
	attr_accessor :lineTypeText
end

