

#ifndef __LRSMESSAGES_H__
#define __LRSMESSAGES_H__

#include <string>
#include <vector>

// Data for a runway system node
struct RSNode
{
        // The ID of the runway system node
        // Example of ID format: RS_NNN-SUBINT-MMM
        // Where NNN is the runway system identifier
        // Where MMM is the sub-interval minute delta
        std::string id_;
        // Runway System ID independent of the sub-interval
        // To be used for checking if next step is for same
        // runway system than previous
        std::string runwaySystem_id_;

        // Configuration ID independent of the sub-interval
        // To be used for checking if next step is for same
        // configuration than previous
        std::string configuration_id_;

        // Possible types of a runway system node
        enum RSNodeType
        {
            Normal, Frozen
        };

        // The type of the runway system node
        RSNodeType type_;

        // The alias of the runway system
        std::string alias_;

};

// Data for a runway system node transition segment
struct RSTransitionSegment
{
        // The ID of the runway system node transition segment
        std::string id_;

        // Possible types of a route segment
        enum RSSegmentType
        {
            Normal, Frozen
        };

        // The type of the route segment
        RSSegmentType type_;

        // The runway system sub-interval node of origin
        std::string originRSNode_;
        // The runway system sub-interval node of destination
        std::string destinationRSNode_;
        // The weight of the transition
        double weight_;

};

// Input data for a schedule request
struct RSScheduleRequest
{
        // ID of request
        std::string id_;

        // The number of schedules to generate.
        int num_schedules_;

        // The runway system-sub-interval pair node ID
        std::string start_node_id_;

        // The node runway system-sub-interval pair node ID where the schedule ends
        std::string end_node_id_;
};

// Output data from a schedule request
struct RSScheduleResponse
{
        // ID of the schedule
        std::string id_;

        // Vector of schedule node IDs for this schedule
        std::vector<std::string> nodes_;

        // Vector of schedule segment IDs for this schedule
        std::vector<std::string> segments_;
};

#endif /* __LRSMESSAGES_H__ */
