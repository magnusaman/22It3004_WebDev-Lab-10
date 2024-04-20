CREATE FUNCTION project(R RELATION(..., **attr1** TYPE, ..., **attrN** TYPE), 
                          attr_list VARCHAR(255))
RETURNS TABLE(..., **attr1** TYPE, ..., **attrN** TYPE)
AS $$
BEGIN
  DECLARE projected_relation TABLE(..., **attr1** TYPE, ..., **attrN** TYPE);
  
  EXECUTE FORMAT(E$'%s', 
                'SELECT ' || attr_list || ' FROM ' || R%TYPE)
                INTO projected_relation;
  
  RETURN projected_relation;
END;
$$ LANGUAGE plpgsql;

-- Example Usage
WITH SampleData (id INT, name VARCHAR(255), age INT) AS (
  SELECT 1, 'Alice', 25 UNION ALL
  SELECT 2, 'Bob', 30 UNION ALL
  SELECT 3, 'Charlie', 28
)
SELECT * FROM project(SampleData, 'name, age');
