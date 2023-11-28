// Datastructures.cc
//
// Student name: Ilari Hietala
// Student email: ilari.hietala@tuni.fi
// Student number: H291752

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return affiliation_count;
}

void Datastructures::clear_all()
{
    affiliation_count = 0;
    affiliation_IDs.clear();
    affiliations.clear();
    publication_IDs.clear();
    publication_graph.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    return affiliation_IDs;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    if (affiliations.find(id) == affiliations.end()) {

        affiliation_count++;
        affiliation_IDs.push_back(id);
        affiliation_IDs_order = 0;

        Affiliation_info info;
        info.xy = xy;
        info.name = name;

        affiliations.insert(std::make_pair(id, info));

        return true;
    } else{
        return false;
    }
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    auto affiliation = affiliations.find(id);

    if (affiliation == affiliations.end()) {
        return NO_NAME;
    } else {
        return (affiliation->second).name;
    }
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    auto affiliation = affiliations.find(id);

    if (affiliation == affiliations.end()) {
        return NO_COORD;
    } else {
        return (affiliation->second).xy;
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    if (affiliation_IDs_order != 1) {
        sort(affiliation_IDs.begin(), affiliation_IDs.end(), [this](auto a, auto b){
            return affiliations[a].name < affiliations[b].name;
        });
        affiliation_IDs_order = 1;
    }

    return affiliation_IDs;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    sort(affiliation_IDs.begin(), affiliation_IDs.end(), [this](auto a, auto b){
        if (sqrt(pow(affiliations[a].xy.x,2) + pow(affiliations[a].xy.y,2)) < sqrt(pow(affiliations[b].xy.x,2) + pow(affiliations[b].xy.y,2))) {
            return true;
        } else if (sqrt(pow(affiliations[a].xy.x,2) + pow(affiliations[a].xy.y,2)) > sqrt(pow(affiliations[b].xy.x,2) + pow(affiliations[b].xy.y,2))) {
            return false;
        } else {
            return affiliations[a].xy.y < affiliations[b].xy.y;
        }
    });
    affiliation_IDs_order = 2;

    return affiliation_IDs;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    if (affiliation_IDs_order != 2) {
        get_affiliations_distance_increasing();
    }

    if (affiliation_count != 0) {
        int low = 0;
        int high = affiliation_count;

        while (low <= high) {
            int mid = (high + low ) / 2;

            auto tester = affiliations[affiliation_IDs[mid]];

            if (tester.xy == xy) {
                return affiliation_IDs[mid];
            } else if (sqrt(pow(tester.xy.x,2) + pow(tester.xy.y,2)) > sqrt(pow(xy.x,2) + pow(xy.y,2))) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
    }

    return NO_AFFILIATION;
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto affiliation = affiliations.find(id);

    if (affiliation == affiliations.end()) {
        return false;
    } else {
        (affiliation->second).xy = newcoord;
        return true;
    }
}

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affilies)
{
    if (publication_graph.find(id) == publication_graph.end()) {

        publication_IDs.push_back(id);

        Publication pub_info;
        pub_info.id = id;
        pub_info.name = name;
        pub_info.year = year;
        pub_info.affiliations = affilies;

        publication_graph.insert(std::make_pair(id, pub_info));

        return true;
    } else{
        return false;
    }
}

std::vector<PublicationID> Datastructures::all_publications()
{
    return publication_IDs;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    auto publication = publication_graph.find(id);

    if (publication ==publication_graph.end()) {
        return NO_NAME;
    } else {
        return (publication->second).name;
    }
}

Year Datastructures::get_publication_year(PublicationID id)
{
    auto publication = publication_graph.find(id);

    if (publication == publication_graph.end()) {
        return NO_YEAR;
    } else {
        return (publication->second).year;
    }
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    auto publication = publication_graph.find(id);

    if (publication == publication_graph.end()){
        std::vector<AffiliationID> affiliation_vec;
        affiliation_vec.push_back(NO_AFFILIATION);
        return affiliation_vec;
    } else {
        return publication_graph[id].affiliations;
    }
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    auto publication = publication_graph.find(id);
    auto publication_parent = publication_graph.find(parentid);

    if (publication == publication_graph.end() && publication_parent == publication_graph.end()) {
        return false;
    } else {
        publication->second.referenced_by = &publication_graph[parentid];
        publication_parent->second.references.push_back(&publication_graph[id]);
        return true;
    }
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    auto pub_references = publication_graph[id].references;
    std::vector<PublicationID> direct_references;

    std::transform(pub_references.begin(), pub_references.end(), std::back_inserter(direct_references), [](auto reference){
        return reference->id;
    });

    return direct_references;
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    auto publication = publication_graph.find(publicationid);
    auto affiliation = affiliations.find(affiliationid);

    if (publication == publication_graph.end() || affiliation == affiliations.end()) {
        return false;
    } else {
        publication->second.affiliations.push_back(affiliationid);
        affiliation->second.publications.push_back(&publication_graph[publicationid] );
        return true;
    }
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    std::vector<PublicationID> pubs;

    if (affiliations.find(id) == affiliations.end()) {
        pubs.push_back(NO_PUBLICATION);
        return pubs;
    }

    for (const auto& pair : publication_graph) {
        if (std::find(pair.second.affiliations.begin(), pair.second.affiliations.end(), id) != pair.second.affiliations.end()) {
            pubs.push_back(pair.first);
        }
    }

    return pubs;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    auto parent_publication = publication_graph[id].referenced_by;

    if (parent_publication == NULL) {
        return NO_PUBLICATION;
    } else {
        return parent_publication->id;
    }
}

std::vector<std::pair<Year, PublicationID>> Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    std::vector<std::pair<Year, PublicationID>> publications_after;

    auto affiliation = affiliations.find(affiliationid);

    if (affiliation == affiliations.end()) {
        publications_after.push_back(std::pair(NO_YEAR, NO_PUBLICATION));
        return publications_after;
    }

    for (auto pub : (*affiliation).second.publications) {
        if (pub->year >= year) {
            publications_after.push_back(std::pair(pub->year, pub->id));
        }
    }

    sort(publications_after.begin(), publications_after.end(), [](auto a, auto b){
        if (a.first < b.first) {
            return true;
        } else if (a.first == b.first) {
            return a.second > b.second;
        } else {
            return false;
        }
    });

    return publications_after;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    std::vector<PublicationID> referenced_by_chain;

    if (publication_graph.find(id) == publication_graph.end()) {
        referenced_by_chain.push_back(NO_PUBLICATION);
        return referenced_by_chain;
    }

    auto publication = publication_graph[id];

    while (publication.referenced_by != NULL) {
        referenced_by_chain.push_back(publication.referenced_by->id);
        publication = *(publication.referenced_by);
    }

    return referenced_by_chain;
}

void Datastructures::get_all_references_recursion(Publication pub, std::vector<PublicationID>& all_references)
{
    for (auto refered_pubs : pub.references) {
        all_references.push_back(refered_pubs->id);
        get_all_references_recursion(*refered_pubs, all_references);
    }
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    std::vector<PublicationID> all_references;

    if (publication_graph.find(id) == publication_graph.end()) {
        all_references.push_back(NO_PUBLICATION);
        return all_references;
    }

    get_all_references_recursion(publication_graph[id], all_references);
    return all_references;
}
std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    std::vector<AffiliationID> affiliations_closest_to;

    sort(affiliation_IDs.begin(), affiliation_IDs.end(), [this, xy](auto a, auto b){
        if (sqrt(pow(xy.x - affiliations[a].xy.x,2) + pow(xy.y - affiliations[a].xy.y,2)) < sqrt(pow(xy.x - affiliations[b].xy.x,2) + pow(xy.y - affiliations[b].xy.y,2))) {
            return true;
        } else if (sqrt(pow(xy.x - affiliations[a].xy.x,2) + pow(xy.y - affiliations[a].xy.y,2)) > sqrt(pow(xy.x - affiliations[b].xy.x,2) + pow(xy.y - affiliations[b].xy.y,2))) {
            return false;
        } else {
            return affiliations[a].xy.y < affiliations[b].xy.y;
        }
    });
    affiliation_IDs_order = 0;

    auto iter = affiliation_IDs.size() < 3 ? affiliation_IDs.end() : affiliation_IDs.begin() + 3;
    std::copy(affiliation_IDs.begin(), iter, std::back_inserter(affiliations_closest_to));

    return affiliations_closest_to;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    if (affiliations.find(id) == affiliations.end()) {
        return false;
    }

    affiliation_count--;
    affiliation_IDs.erase(std::find(affiliation_IDs.begin(), affiliation_IDs.end(), id));
    affiliations.erase(id);

    auto publications_to_check = get_publications(id);

    for (auto pub : publications_to_check) {
        auto pub_affilies = publication_graph[pub].affiliations;
        if (std::find(pub_affilies.begin(), pub_affilies.end(), id) != pub_affilies.end()) {
            pub_affilies.erase(std::find(pub_affilies.begin(), pub_affilies.end(), id));
        }

    }

    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    auto id1_parents = get_referenced_by_chain(id1);
    auto id2_parents = get_referenced_by_chain(id2);

    for (auto id1_parent : id1_parents) {
        if (std::find(id2_parents.begin(), id2_parents.end(), id1_parent) != id2_parents.end()) {
            return id1_parent;
        }
    }

    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    if (publication_graph.find(publicationid) == publication_graph.end()) {
        return false;
    }

    Publication* target = &publication_graph[publicationid];

    for (auto references : target->references) {
        references->referenced_by = NULL;
    }

    for (auto &affiliation : affiliations) {

        auto affilie_pubs = affiliation.second.publications;

        if (std::find(affilie_pubs.begin(), affilie_pubs.end(), target) != affilie_pubs.end()) {
           affilie_pubs.erase(std::find(affilie_pubs.begin(),affilie_pubs.end(), target));
        }
    }

    publication_IDs.erase(std::find(publication_IDs.begin(), publication_IDs.end(), publicationid));
    publication_graph.erase(publicationid);
    return true;
}



