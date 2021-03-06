#include "triangle2.h"
#define EPSILON 0.000001f

Triangle2::Triangle2( const glm::vec3 v1, const glm::vec3 v2,const glm::vec3 v3, Material material):
					Primitive::Primitive{material}, v1{v1}, v2{v2}, v3{v3}
{}

bool Triangle2::intersect(const Ray &ray,
	IntersectionRecord &intersection_record) const
{
	glm::vec3 edge1, edge2, tvec, pvec, qvec;
	float det, inv_det, t, u, v;

	edge1 = v2 - v1;
	edge2 = v3 - v1;
	pvec = glm::cross(ray.direction_, edge2);
	det = glm::dot(edge1, pvec);

	if (det > -EPSILON && det < EPSILON) return false;

	inv_det = 1.0f / det;
	tvec = ray.origin_ - v1;

	u = glm::dot(tvec, pvec)*inv_det;
	if (u < 0.0f || u > 1.0f) return false;

	qvec = glm::cross(tvec, edge1);

	v = glm::dot(ray.direction_, qvec)*inv_det;
	if (v < 0.0f || (u + v) > 1.0f) return false;

	t = glm::dot(edge2, qvec)*inv_det;

	intersection_record.t_ = t;
	intersection_record.position_ = ray.origin_ + intersection_record.t_ * ray.direction_;

	intersection_record.normal_ = glm::normalize(glm::cross(v2 - v1, v3 - v1));
	if (glm::dot(intersection_record.normal_, ray.direction_) > 0.0f)
		intersection_record.normal_ = -intersection_record.normal_;

	intersection_record.material_ = material_;

	return true;
}

AABB Triangle2::getAABB(void) const
{
    AABB aabb;

    aabb.min_ = glm::min(glm::min(v1, v2), v3);
    aabb.max_ = glm::max(glm::max(v1, v2), v3);
    aabb.centroid_ = (1.0f / 3.0f) * (v1 + v2 + v3);
    return aabb;
}